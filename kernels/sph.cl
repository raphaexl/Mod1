# define GRAVITY        (9.8f)                                 			 	//  Gravity constante
# define G              ((float3){0.0f, -1200.0f * GRAVITY, 0.0f})    		//  External Gravity Force
# define REST_DENS      (1000.0f)                               			//  Rest Density
# define GAS_CONST      (2000.0f)
# define H              (16.0f)                                 			//  Kernel Radius
# define HSQ            (H * H)                                 			//  Kernel Radius Square
# define MASS           (65.0f)                                 			//  Assumption that all paricules have this mass
# define VISC           (250.f)                                 			//  Viscosity constant
# define DT             (0.0008f)                               			//  Integration timestep

# define POLY6          (315.0f / (65.0f * M_PI * pow(H, 9.0f))) 			//  Maller Kernel functions and Gradients
# define SPIKY_GRAD     (-45.0f / (M_PI * pow(H, 6.0f)))
# define VISC_LAP       (45.0f / (M_PI * pow(H, 6.0f)))

# define EPS            (H)                                     			//  For Boundry checkings
# define BOUND_DAMPING  (-0.05f)                                 			//  For Attenuation of velocity

# define MAX_PARTICLES  (2500)                                  			//  Max Particles number
# define DAM_PARTICLES  (1024)                                    			//  For The Begining
# define BLK_PARTICLES  (250)

void   ComputeDensityPressure(__global float3 *pos, __global float3 *vel, __global float3 *force, __global float *rho, __global float *pres, unsigned int i, unsigned int size);
void    ComputeForces(__global float3 *pos, __global float3 *vel, __global float3 *force, __global float *rho, __global float *pres, unsigned int i, unsigned int size);
void   Integrate(__global float3 *pos, __global float3 *vel, __global float3 *force, __global float *rho, __global float *pres, unsigned int i, float w_w, float w_h);



void   ComputeDensityPressure(__global float3 *pos, __global float3 *vel, __global float3 *force, __global float *rho, __global float *pres, unsigned int i, unsigned int size)
{
		rho[i] = .0f;
		for (unsigned int j = 0; j < size; j++)
		{
			float3   rij = pos[j] - pos[i];
			float r2 = pow(length(rij), 2.0f);
			if (r2 < HSQ)
			{
				//Note that this computation is symetric
				rho[i] += MASS * POLY6 * (float)pow((float)(HSQ - r2), (float)3.0f);
			}
		}
		pres[i] = GAS_CONST * (rho[i] - REST_DENS);
}

void    ComputeForces(__global float3 *pos, __global float3 *velocity, __global float3 *force, __global float *rho, __global float *pres, unsigned int i, unsigned int size)
{
		float3  fpressure = float3(0.0, 0.0, 0.0);
		float3  fviscocity = float3(0.0, 0.0, 0.0);

		for (unsigned int j = 0; j < size; j++)
		{	
			if (i == j)
				continue ;
			float3  rij = pos[j] - pos[i];
			float   r = length(rij);

			if (r < H)
			{
				float3 tmp;
				tmp = ((float)(((-MASS / (2.0f * rho[j])) * SPIKY_GRAD * pow(H - r, 2.0f))) * (pres[i] + pres[j])) * normalize(rij);
					fpressure = fpressure + tmp;
				fviscocity = fviscocity + (float)(VISC * MASS / rho[j] * VISC_LAP * (H - r)) * (velocity[j] - velocity[i]);
			}
		}
		float3 fgravity = rho[i] * G;
		force[i] = fpressure + fviscocity + fgravity;
}

void   Integrate(__global float3 *pos, __global float3 *velocity, __global float3 *force, __global float *rho, __global float *pres, unsigned int i, float v_w, float v_h)
{
		//Forward Euler Integration
		//  p.v += DT*p.f/p.rho;
		//	p.x += DT*p.v;
		velocity[i] +=  DT * force[i] / rho[i];
		pos[i] += DT * velocity[i];

		if(pos[i].x-EPS < -v_w)
		{
			velocity[i].x *= BOUND_DAMPING;
			pos[i].x = EPS - v_w;
		}
		if(pos[i].x + EPS> v_w)
		{
			velocity[i].x *= BOUND_DAMPING;
			pos[i].x = v_w-EPS;
		}
	//	float hz = TerrainHeight(this->terrain, pos[i].x, pos[i].z);
	//	if(pos[i].y-EPS <= (16.0 * hz - 16.0 / 2.0))
	//	{
	//		velocity[i].y *= BOUND_DAMPING;
	//		pos[i].y =  (16.0 * hz - 16.0 / 2.0) + EPS;
	//	}
		if(pos[i].y-EPS <= 0.0f)
		{
			velocity[i].y = 0.0;
			//velocity[i].y *= BOUND_DAMPING;
			pos[i].y =  EPS;
		}
	/*	if(pos[i].y + EPS > 200)
		{
			velocity[i].y *= BOUND_DAMPING;
			pos[i].y = 200 - EPS;
		}*/
		if(pos[i].z-EPS < -v_h)
		{
			velocity[i].z *= BOUND_DAMPING;
			pos[i].z = -v_h + EPS;
		}
		if(pos[i].z+EPS > v_h)
		{
			velocity[i].z *= BOUND_DAMPING;
			pos[i].z = v_h -EPS;
		}
}

__kernel void smooth_particles(__global float3 *pos, __global float3 *vel, __global float3 *force, __global float *rho, __global float *pres, __global float *terrain, unsigned int size, float v_w, float v_h)
{
	const int i = get_global_id(0);
	ComputeDensityPressure(pos, vel, force, rho, pres, i, size);
	ComputeForces(pos, vel, force, rho, pres, i, size);
	Integrate(pos, vel, force, rho, pres, i, v_w, v_h);
	terrain[i] = terrain[i];
}
