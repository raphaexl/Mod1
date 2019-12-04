/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 17:42:14 by ebatchas          #+#    #+#             */
/*   Updated: 2019/11/19 12:13:28 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "window.hpp"

# define MAX_SOURCE_SIZE (0x1000000)

typedef struct			s_opencl
{
	cl_platform_id		platform_id;
	cl_device_id		device_id;
	cl_uint				ret_num_platforms;
	cl_uint				ret_num_devices;
	cl_int				ret;
	cl_context			context;
	cl_command_queue	command_queue;
	cl_mem				cpu_mem_pos;
	cl_mem				cpu_mem_vel;
	cl_mem				cpu_mem_force;
	cl_mem				cpu_mem_rho;
	cl_mem				cpu_mem_pres;
	cl_mem				cpu_mem_terrain;
	cl_program			program;
	cl_kernel			kernel1;
	cl_kernel			kernel2;
	cl_kernel			kernel3;
	size_t				global_iterm_size;
	size_t				local_iterm_size;
}						t_opencl;

cl_platform_id			ft_cl_platform(void);
cl_device_id			ft_cl_device(cl_platform_id plateform_id);
cl_context				ft_cl_context(cl_device_id *device_id);
cl_command_queue		ft_cl_command_queue(cl_context context, cl_device_id device_id);
cl_program				ft_cl_program(cl_context c, char *file_name);
void					ft_opencl_init(t_opencl *opencl, char *kernel_file);
void					ft_opencl_mem(t_opencl *opencl, SPH *sph);
void					ft_opencl_kernel(t_opencl *opencl, SPH *sph);
void					ft_opencl_run(t_opencl *opencl, SPH *sph);
void					ft_opencl_quit(t_opencl *opencl);

cl_float3				ft_cl_float3(float x, float y, float z);
