/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sph.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 19:58:26 by ebatchas          #+#    #+#             */
/*   Updated: 2019/12/04 14:21:22 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/mod1.hpp"

SPH::SPH()
{
	this->v_w = VIEW_WIDTH;
	this->v_h =  VIEW_HEIGHT;
	this->size = DEFAULT_TERRAIN_SIZE;
}

void    SPH::InitSPH(std::vector<float>heights, float max_height)
{
	std::cout<<"DAM Break Initialisation"<<std::endl;

	float		width = (size - 1);
	float		height = (size - 1);
	float		h_width = width * 0.5;
	float		h_height = height * 0.5;

	this->v_w = ((width + 1) / 2.0) * 16.0 + 8.0;
	this->v_h = ((height + 1) / 2.0) * 16.0 + 8.0;

	int max_kheight = max_height;
	this->terrain = heights;
	for (int k{0}; k < max_kheight; k++)
		for (int j{0}; j < size; j++)
		{
			for (int i{0}; i < size; i++)
			{
				unsigned int index = j * size + i;

				if (heights[index] * 16.0 > k * 16.0)
				{
					if (particles.size() < (size_t)DAM_PARTICLES * max_kheight)
					{
						glm::vec3	vertex;
						float		s = float(i) / float(size - 1);
						float		t = float(j) / float(size - 1);

					//	vertex = glm::vec3(s * width - h_width, heights[index] * 16.0, t * height - h_height);
						vertex = glm::vec3(s * width - h_width, k * 16.0, t * height - h_height);
						vertex = glm::vec3(vertex.x * 16.0, vertex.y , vertex.z * 16.0);
						particles.push_back(Particle(vertex.x, vertex.y, vertex.z));
						int current = particles.size() - 1;
						particles[current].mass = MASS;
						particles[current].is_active = 0;
					 int n_index = particles.size() - 1;
					pos[n_index] = ft_cl_float3(vertex.x, vertex.y, vertex.z);
					velocity[n_index] = ft_cl_float3(0.0, 0.0, 0.0);
					force[n_index] = ft_cl_float3(0.0, 0.0, 0.0);
					rho[n_index] = 0.0;
					pressure[n_index] = 0.0;
					this->heights[n_index] = ft_cl_float3(0.0,  0.0, 0.0);
					actives[n_index] = 0;
					}
				}
			}
		}
	for (int k{0}; k < N_BLOCKS; k++)
		for (int j{0}; j < size; j++)
		{
			for (int i{0}; i < size; i++)
			{

				if (particles.size() < (size_t)MAX_PARTICLES)
				{
					glm::vec3	vertex;
					float		s = float(i) / float(size - 1);
					float		t = float(j) / float(size - 1);
					float jitter = static_cast <float> (rand()) /static_cast<float> (RAND_MAX);
					vertex = glm::vec3(s * width - h_width, k * 16.0 + 200, t * height - h_height);
					particles.push_back(Particle((vertex.x + jitter) * 16.0, vertex.y, vertex.z * 16.0));
					int current = particles.size() - 1;
					particles[current].mass = MASS;
					particles[current].is_active = 1;
					actives[current] = 1;
				}
			}
		}
	std::cout<<"Drawing size : "<<particles.size()<<std::endl;
	std::cout<<"width : "<<v_w<<"height : "<<v_h<<std::endl;
}

//P = k(q - qo);

void   SPH::ComputeDensityPressure(void)
{
	for (auto &pi : particles)
	{
		pi.rho = .0f;
		for (auto &pj : particles)
		{
			glm::vec3   rij = pj.pos - pi.pos;
			float r2 = vec3_square_norm(rij);
			if (r2 < HSQ)
			{
				//Note that this computation is symetric
				pi.rho += pi.mass * POLY6 * pow(HSQ - r2, 3.0f);
			}
		}
		pi.pressure = GAS_CONST * (pi.rho - REST_DENS);
	}
}


void    SPH::ComputeForces(void)
{
	for (auto &pi : particles)
	{
		glm::vec3  fpressure(0.0, 0.0, 0.0);
		glm::vec3  fviscocity(0.0, 0.0, 0.0);

		for (auto &pj : particles)
		{
			if (&pi == &pj)
				continue;
			glm::vec3  rij = vec3_sub(pj.pos, pi.pos);
			float   r = vec3_norm(rij);

			if (r < H)
			{
				glm::vec3 tmp;
				tmp = vec3_kmult((-pi.mass * (pi.pressure + pj.pressure)/ (2.0f * pj.rho)) * SPIKY_GRAD * pow(H - r, 2.0f), vec3_normalize(rij)),
					fpressure = vec3_sum(fpressure, tmp);
				fviscocity = vec3_sum(fviscocity, vec3_kmult(VISC * pi.mass / pj.rho * VISC_LAP * (H - r), vec3_sub(pj.velocity, pi.velocity)));
				// compute pressure force contribution
				//fpress += -rij.normalized()*MASS*(pi.p + pj.p)/(2.f * pj.rho) * SPIKY_GRAD*pow(H-r,2.f);
				// compute viscosity force contribution
				//fvisc += VISC*MASS*(pj.v - pi.v)/pj.rho * VISC_LAP*(H-r);
			}
		}
			glm::vec3 fgravity = pi.rho * G;
		if (pi.is_active)
			pi.force = fpressure + fviscocity + fgravity;
		else
			pi.force = -fgravity + fviscocity;
	}
}

float	Height(std::vector<float> height, int x, int y)
{
	int index;
	int 	size = DEFAULT_TERRAIN_SIZE;

	index = y  * size + x;
	/*if(height[index] < 0.01)
	  return (0.0);
	  else
	  std::cout<<"Here for example : "<<height[index]<<std::endl;*/
	return (height[index]);
}

float	barycentric(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec2 xz)
{
	float	det = (v2.z - v3.z) * (v1.x - v3.x) + (v3.x - v2.x) * (v1.z - v3.z);
	float	l1 = ((v2.z - v3.z) * (xz.x - v3.x) + (v3.x - v2.x) * (xz.y - v3.z)) / det;
	float	l2 = ((v3.z - v1.z) * (xz.x - v3.x) + (v1.x - v3.x) * (xz.y - v3.z)) / det;
	float	l3 = 1.0f - l1 - l2;
	return (l1 * v1.y + l2 * v2.y + l3 * v3.y);
}

float	TerrainHeight(std::vector<float>  heights, float worldx, float worldz)
{
	float	h_anz = .0;
	int 	size = DEFAULT_TERRAIN_SIZE;

	float		width = (size - 1);
	float		height = (size - 1);
	float		h_width = width * 0.5;
	float		h_height = height * 0.5;

	worldx /= H;
	worldz /= H;
	float		s = (worldx + h_width) /   width;
	float		t = (worldz +  h_height) /  height;

	int		x = (s * (size - 1));
	int		z = (t * (size - 1));
	/*	std::cout<<"worldx : "<<worldx<<"worldz : "<<worldz<<std::endl;
		std::cout<<"s : "<<s<<" t : "<<t<<std::endl;
		std::cout<<"x : "<<x<<" z : "<<z<<std::endl;
		std::cout<<"Height (x, z) is : "<<Height(heights, x, z)<<std::endl;
		std::cout<<"Height (x + 1, z) is : "<<Height(heights, x + 1, z)<<std::endl;
		std::cout<<"Height (x, z + 1) is : "<<Height(heights, x, z + 1)<<std::endl;
		std::cout<<"Height (x + 1, z + 1) is : "<<Height(heights, x + 1, z + 1)<<std::endl;*/
	return (Height(heights, x, z));
	if (s <= 1.0 - t)
		h_anz = barycentric(glm::vec3(0.0f, Height(heights, x, z), 0.0f),
				glm::vec3(1.0f, Height(heights, x - 1, z), 0.0f),
				glm::vec3(0.0f, Height(heights, x, z - 1), 1.0f),
				glm::vec2(s, t));
	else
	{
		h_anz = barycentric(glm::vec3(1.0f, Height(heights, x - 1, z), 0.0f),
				glm::vec3(1.0f, Height(heights, x - 1, z - 1), 1.0f),
				glm::vec3(0.0f, Height(heights, x, z - 1), 1.0f),
				glm::vec2(s, t));
	}
	//	std::cout<<"Height is : "<<h_anz<<std::endl;
	//	exit(0);
	return (h_anz);
}


void   SPH::Integrate(void)
{
	for (auto &p : particles)
	{
		if (!p.is_active)
			continue;
		//Forward Euler Integration
		//  p.v += DT*p.f/p.rho;
		//	p.x += DT*p.v;

		p.velocity +=  DT * p.force / p.rho;
		p.pos += DT * p.velocity;
		//float hz = TerrainHeight(this->terrain, p.pos.x, p.pos.z);
		for (auto &pj : particles)
		{
			if (pj.is_active)
			continue;
			if (&p == &pj)
				continue;
			if (p.pos.y > pj.pos.y)
			{
			if (vec3_norm(p.velocity) > 0.01)
				p.velocity = glm::vec3(0.0f);
			else
			{
				p.velocity.y = ((MASS - GROUND_MASS)/(MASS + GROUND_MASS)) * p.velocity.y;
				p.velocity.x = ((MASS - GROUND_MASS)/(MASS + GROUND_MASS)) * p.velocity.x;
			}

			}

		}
		if(p.pos.x-EPS < -this->v_w)
		{
			p.velocity.x *= BOUND_DAMPING;
			p.pos.x = EPS - this->v_w;
		}
		if(p.pos.x+EPS> this->v_w)
		{
			p.velocity.x *= BOUND_DAMPING;
			p.pos.x = this->v_w-EPS;

		}
				/*	if(p.pos.y + EPS > 200)
			{
			p.velocity.y *= BOUND_DAMPING;
			p.pos.y = 200 -  EPS;
			}*/
		/*	if(p.pos.y - EPS < 0.0)
			{
			p.velocity.y *= BOUND_DAMPING;
			p.pos.y =  EPS;
			}*/
		if(p.pos.z-EPS < - this->v_h)
		{
			p.velocity.z *= BOUND_DAMPING;
			p.pos.z = -this->v_h + EPS;
		}
		if(p.pos.z+EPS > this->v_h)
		{
			p.velocity.z *= BOUND_DAMPING;
			p.pos.z = this->v_h -EPS;
		}
	}
}

void    SPH::Update(void)
{
	ComputeDensityPressure();
	ComputeForces();
	Integrate();
}
