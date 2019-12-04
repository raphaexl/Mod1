/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sph.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 19:52:04 by ebatchas          #+#    #+#             */
/*   Updated: 2019/12/04 14:32:29 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once
# include "terrain.hpp"

# define VIEW_WIDTH (100.0) * 1.0f
# define VIEW_HEIGHT (100.0) * 1.0f

# define GRAVITY        (9.8f)                                  //  Gravity constante
# define G              (glm::vec3(0.0f, -1200.0f * GRAVITY, 0.0f))    //  External Gravity Force
# define REST_DENS      (1000.0f)                               //  Rest Density
# define GAS_CONST      (2000.0f)                               
# define H              (16.0f)                                 //  Kernel Radius
# define HSQ            (H * H)                                 //  Kernel Radius Square
# define MASS           (65.0f)                                 //  Assumption that all paricules have this mass
# define GROUND_MASS    (650.0f * 1.2)
# define VISC           (250.f)                                 //  Viscosity constant
# define DT             (0.0008f)                               //  Integration timestep

# define POLY6          (315.0f / (65.0f * M_PI * pow(H, 9.0))) //  Maller Kernel functions and Gradients
# define SPIKY_GRAD     (-45.0f / (M_PI * pow(H, 6.0)))
# define VISC_LAP       (45.0f / (M_PI * pow(H, 6.0)))

# define EPS            (H)                                     //  For Boundry checkings
# define BOUND_DAMPING  (-0.05f)                                 //  For Attenuation of velocity

# define N_BLOCKS      1
# define N_MAX 10
# define DAM_PARTICLES  (DEFAULT_TERRAIN_SIZE * DEFAULT_TERRAIN_SIZE * N_BLOCKS)   //  For The Begining
# define MAX_PARTICLES  (DEFAULT_TERRAIN_SIZE * DEFAULT_TERRAIN_SIZE * N_MAX)   //  For The Begining


class Particle
{
	public:
		glm::vec3       pos;
		glm::vec3       velocity;
		glm::vec3       force;
		int				is_active;
		float           rho;
		float           pressure;
		float			mass;
		Particle(float posx, float posy, float posz)
		{
			memset(this, 0, sizeof(Particle));
			this->pos.x = posx;
			this->pos.y = posy;
			this->pos.z = posz;
		};
};

class SPH
{
	public:
		int						size;
		cl_float				v_w;
		cl_float				v_h;
		cl_float3       		pos[MAX_PARTICLES];
		cl_float3       		velocity[MAX_PARTICLES];
		cl_float3       		force[MAX_PARTICLES];
		cl_float3       		heights[MAX_PARTICLES];
		cl_int		     		actives[MAX_PARTICLES];
		cl_float           		rho[MAX_PARTICLES];
		cl_float          	 	pressure[MAX_PARTICLES];
		std::vector<Particle>	particles;
		std::vector<float>		terrain;
		void    				InitSPH(std::vector<float>heights, float max_height);
		void                    Integrate(void);
		void                    ComputeDensityPressure(void);
		void                    ComputeForces(void);
		void                    Update(void);
		SPH();
		~SPH(){particles.clear();};
};

glm::vec3               vec3(float x, float y, float z);
glm::vec3               vec3_sub(glm::vec3 v1, glm::vec3 v2);
glm::vec3               vec3_sum(glm::vec3 v1, glm::vec3 v2);
glm::vec3               vec3_mult(glm::vec3 v1, glm::vec3 v2);
glm::vec3               vec3_normalize(glm::vec3 v);
glm::vec3               vec3_kmult(float k, glm::vec3 v2);
float                   vec3_square_norm(glm::vec3 v);
float                   vec3_norm(glm::vec3 v);
