/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 17:40:23 by ebatchas          #+#    #+#             */
/*   Updated: 2019/12/04 14:38:08 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/mod1.hpp"

void	ft_opencl_init(t_opencl *opencl, char *kernel_file)
{
	opencl->platform_id = ft_cl_platform();
	opencl->device_id = ft_cl_device(opencl->platform_id);
	opencl->context = ft_cl_context(&opencl->device_id);
	opencl->command_queue = ft_cl_command_queue(opencl->context, opencl->device_id);
	opencl->program = ft_cl_program(opencl->context, kernel_file);
}

void	ft_opencl_mem(t_opencl *opencl, SPH *sph)
{
	cl_int			ret;
	size_t			size;

	size = sph->particles.size();
	opencl->cpu_mem_pos = clCreateBuffer(opencl->context, CL_MEM_READ_WRITE, size * sizeof(cl_float3), NULL, &ret);
	opencl->cpu_mem_vel = clCreateBuffer(opencl->context, CL_MEM_READ_WRITE, size * sizeof(cl_float3), NULL, &ret);
	opencl->cpu_mem_force = clCreateBuffer(opencl->context, CL_MEM_READ_WRITE, size * sizeof(cl_float3), NULL, &ret);
	opencl->cpu_mem_pres = clCreateBuffer(opencl->context, CL_MEM_READ_WRITE, size * sizeof(cl_float), NULL, &ret);
	opencl->cpu_mem_rho = clCreateBuffer(opencl->context, CL_MEM_READ_WRITE, size * sizeof(cl_float), NULL, &ret);
	opencl->cpu_mem_terrain = clCreateBuffer(opencl->context, CL_MEM_READ_WRITE, size * sizeof(cl_float), NULL, &ret);
}

void	ft_opencl_kernel(t_opencl *opencl, SPH *sph)
{
	cl_int		ret;

	ret = clBuildProgram(opencl->program, 1, &opencl->device_id, NULL, NULL, NULL);
	if (ret == CL_BUILD_PROGRAM_FAILURE)
	{
		size_t	log_size;
		char	err[256];

		clGetProgramBuildInfo(opencl->program, opencl->device_id, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
		clGetProgramBuildInfo(opencl->program, opencl->device_id, CL_PROGRAM_BUILD_LOG, log_size, err, NULL);
		puts(err);
	}
	opencl->kernel1 = clCreateKernel(opencl->program, "ComputeDensityPressure", &ret);
	opencl->kernel2 = clCreateKernel(opencl->program, "ComputeForces", &ret);
	opencl->kernel3 = clCreateKernel(opencl->program, "Integrate", &ret);
	cl_uint		size = sph->particles.size();
	cl_float	v_w = sph->v_w;
	cl_float	v_h = sph->v_h;

	ret = clSetKernelArg(opencl->kernel1, 0, sizeof(cl_mem), (void *)&opencl->cpu_mem_pos);
	ret = clSetKernelArg(opencl->kernel1, 1, sizeof(cl_mem), (void *)&opencl->cpu_mem_vel);
	ret = clSetKernelArg(opencl->kernel1, 2, sizeof(cl_mem), (void *)&opencl->cpu_mem_force);
	ret = clSetKernelArg(opencl->kernel1, 3, sizeof(cl_mem), (void *)&opencl->cpu_mem_rho);
	ret = clSetKernelArg(opencl->kernel1, 4, sizeof(cl_mem), (void *)&opencl->cpu_mem_pres);
	ret = clSetKernelArg(opencl->kernel1, 5, sizeof(cl_uint), (void *)&size);
	
	ret = clSetKernelArg(opencl->kernel2, 0, sizeof(cl_mem), (void *)&opencl->cpu_mem_pos);
	ret = clSetKernelArg(opencl->kernel2, 1, sizeof(cl_mem), (void *)&opencl->cpu_mem_vel);
	ret = clSetKernelArg(opencl->kernel2, 2, sizeof(cl_mem), (void *)&opencl->cpu_mem_force);
	ret = clSetKernelArg(opencl->kernel2, 3, sizeof(cl_mem), (void *)&opencl->cpu_mem_rho);
	ret = clSetKernelArg(opencl->kernel2, 4, sizeof(cl_mem), (void *)&opencl->cpu_mem_pres);
	ret = clSetKernelArg(opencl->kernel2, 5, sizeof(cl_uint), (void *)&size);

	ret = clSetKernelArg(opencl->kernel3, 0, sizeof(cl_mem), (void *)&opencl->cpu_mem_pos);
	ret = clSetKernelArg(opencl->kernel3, 1, sizeof(cl_mem), (void *)&opencl->cpu_mem_vel);
	ret = clSetKernelArg(opencl->kernel3, 2, sizeof(cl_mem), (void *)&opencl->cpu_mem_force);
	ret = clSetKernelArg(opencl->kernel3, 3, sizeof(cl_mem), (void *)&opencl->cpu_mem_rho);
	ret = clSetKernelArg(opencl->kernel3, 4, sizeof(cl_mem), (void *)&opencl->cpu_mem_pres);
	ret = clSetKernelArg(opencl->kernel3, 5, sizeof(cl_mem), (void *)&opencl->cpu_mem_terrain);
	ret = clSetKernelArg(opencl->kernel3, 6, sizeof(cl_uint), (void *)&size);
	ret = clSetKernelArg(opencl->kernel3, 7, sizeof(cl_float), (void *)&v_w);
	ret = clSetKernelArg(opencl->kernel3, 8, sizeof(cl_float), (void *)&v_h);
}

void	ft_opencl_run(t_opencl *opencl, SPH *sph)
{
	size_t		global_iterm_size;
	size_t		local_iterm_size;
	cl_int		ret;
	size_t		size;

	size = sph->particles.size();
	global_iterm_size = size;
	local_iterm_size = 19 ;
	//Kernel 1
	clEnqueueWriteBuffer(opencl->command_queue, opencl->cpu_mem_pos, CL_TRUE, 0, size * sizeof(cl_float3), sph->pos, 0, NULL, NULL);
	clEnqueueWriteBuffer(opencl->command_queue, opencl->cpu_mem_vel, CL_TRUE, 0, size * sizeof(cl_float3), sph->velocity, 0, NULL, NULL);
	clEnqueueWriteBuffer(opencl->command_queue, opencl->cpu_mem_force, CL_TRUE, 0, size * sizeof(cl_float3), sph->force, 0, NULL, NULL);
	clEnqueueWriteBuffer(opencl->command_queue, opencl->cpu_mem_rho, CL_TRUE, 0, size * sizeof(cl_float), sph->rho, 0, NULL, NULL);
	clEnqueueWriteBuffer(opencl->command_queue, opencl->cpu_mem_pres, CL_TRUE, 0, size * sizeof(cl_float), sph->pressure, 0, NULL, NULL);
	ret = clEnqueueNDRangeKernel(opencl->command_queue, opencl->kernel1, 1, NULL, &global_iterm_size, &local_iterm_size, 0, NULL, NULL);
//	clEnqueueTask(opencl->command_queue, 0, 0, 0, 0);
	clEnqueueReadBuffer(opencl->command_queue, opencl->cpu_mem_pos, CL_TRUE, 0, size * sizeof(cl_float3), sph->pos, 0, NULL, NULL);
	clEnqueueReadBuffer(opencl->command_queue, opencl->cpu_mem_vel, CL_TRUE, 0, size * sizeof(cl_float3), sph->velocity, 0, NULL, NULL);
	clEnqueueReadBuffer(opencl->command_queue, opencl->cpu_mem_force, CL_TRUE, 0, size * sizeof(cl_float3), sph->force, 0, NULL, NULL);
	clEnqueueReadBuffer(opencl->command_queue, opencl->cpu_mem_rho, CL_TRUE, 0, size * sizeof(cl_float), sph->rho, 0,  NULL, NULL);
	clEnqueueReadBuffer(opencl->command_queue, opencl->cpu_mem_pres, CL_TRUE, 0, size * sizeof(cl_float), sph->pressure, 0, NULL, NULL);
	//Kernel 2
	clEnqueueWriteBuffer(opencl->command_queue, opencl->cpu_mem_pos, CL_TRUE, 0, size * sizeof(cl_float3), sph->pos, 0, NULL, NULL);
	clEnqueueWriteBuffer(opencl->command_queue, opencl->cpu_mem_vel, CL_TRUE, 0, size * sizeof(cl_float3), sph->velocity, 0, NULL, NULL);
	clEnqueueWriteBuffer(opencl->command_queue, opencl->cpu_mem_force, CL_TRUE, 0, size * sizeof(cl_float3), sph->force, 0, NULL, NULL);
	clEnqueueWriteBuffer(opencl->command_queue, opencl->cpu_mem_rho, CL_TRUE, 0, size * sizeof(cl_float), sph->rho, 0, NULL, NULL);
	clEnqueueWriteBuffer(opencl->command_queue, opencl->cpu_mem_pres, CL_TRUE, 0, size * sizeof(cl_float), sph->pressure, 0, NULL, NULL);
	ret = clEnqueueNDRangeKernel(opencl->command_queue, opencl->kernel2, 1, NULL, &global_iterm_size, &local_iterm_size, 0, NULL, NULL);
//	clEnqueueTask(opencl->command_queue, 0, 0, 0, 0);
	clEnqueueReadBuffer(opencl->command_queue, opencl->cpu_mem_pos, CL_TRUE, 0, size * sizeof(cl_float3), sph->pos, 0, NULL, NULL);
	clEnqueueReadBuffer(opencl->command_queue, opencl->cpu_mem_vel, CL_TRUE, 0, size * sizeof(cl_float3), sph->velocity, 0, NULL, NULL);
	clEnqueueReadBuffer(opencl->command_queue, opencl->cpu_mem_force, CL_TRUE, 0, size * sizeof(cl_float3), sph->force, 0, NULL, NULL);
	clEnqueueReadBuffer(opencl->command_queue, opencl->cpu_mem_rho, CL_TRUE, 0, size * sizeof(cl_float), sph->rho, 0,  NULL, NULL);
	clEnqueueReadBuffer(opencl->command_queue, opencl->cpu_mem_pres, CL_TRUE, 0, size * sizeof(cl_float), sph->pressure, 0, NULL, NULL);
	//Kernel 3
	clEnqueueWriteBuffer(opencl->command_queue, opencl->cpu_mem_pos, CL_TRUE, 0, size * sizeof(cl_float3), sph->pos, 0, NULL, NULL);
	clEnqueueWriteBuffer(opencl->command_queue, opencl->cpu_mem_vel, CL_TRUE, 0, size * sizeof(cl_float3), sph->velocity, 0, NULL, NULL);
	clEnqueueWriteBuffer(opencl->command_queue, opencl->cpu_mem_force, CL_TRUE, 0, size * sizeof(cl_float3), sph->force, 0, NULL, NULL);
	clEnqueueWriteBuffer(opencl->command_queue, opencl->cpu_mem_rho, CL_TRUE, 0, size * sizeof(cl_float), sph->rho, 0, NULL, NULL);
	clEnqueueWriteBuffer(opencl->command_queue, opencl->cpu_mem_pres, CL_TRUE, 0, size * sizeof(cl_float), sph->pressure, 0, NULL, NULL);
	ret = clEnqueueNDRangeKernel(opencl->command_queue, opencl->kernel3, 1, NULL, &global_iterm_size, &local_iterm_size, 0, NULL, NULL);
//	clEnqueueTask(opencl->command_queue, 0, 0, 0, 0);
	clEnqueueReadBuffer(opencl->command_queue, opencl->cpu_mem_pos, CL_TRUE, 0, size * sizeof(cl_float3), sph->pos, 0, NULL, NULL);
	clEnqueueReadBuffer(opencl->command_queue, opencl->cpu_mem_vel, CL_TRUE, 0, size * sizeof(cl_float3), sph->velocity, 0, NULL, NULL);
	clEnqueueReadBuffer(opencl->command_queue, opencl->cpu_mem_force, CL_TRUE, 0, size * sizeof(cl_float3), sph->force, 0, NULL, NULL);
	clEnqueueReadBuffer(opencl->command_queue, opencl->cpu_mem_rho, CL_TRUE, 0, size * sizeof(cl_float), sph->rho, 0,  NULL, NULL);
	clEnqueueReadBuffer(opencl->command_queue, opencl->cpu_mem_pres, CL_TRUE, 0, size * sizeof(cl_float), sph->pressure, 0, NULL, NULL);

//	exit(EXIT_FAILURE);
}


void	ft_opencl_quit(t_opencl *opencl)
{
	cl_int		ret;

	ret = clFlush(opencl->command_queue);
	ret = clFinish(opencl->command_queue);
	ret = clReleaseKernel(opencl->kernel1);
	ret = clReleaseKernel(opencl->kernel2);
	ret = clReleaseKernel(opencl->kernel3);
	ret = clReleaseProgram(opencl->program);
	ret = clReleaseMemObject(opencl->cpu_mem_pos);
	ret = clReleaseMemObject(opencl->cpu_mem_vel);
	ret = clReleaseMemObject(opencl->cpu_mem_force);
	ret = clReleaseMemObject(opencl->cpu_mem_rho);
	ret = clReleaseMemObject(opencl->cpu_mem_pres);
	ret = clReleaseMemObject(opencl->cpu_mem_terrain);
	ret = clReleaseCommandQueue(opencl->command_queue);
	ret = clReleaseContext(opencl->context);
}
