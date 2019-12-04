/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 17:39:42 by ebatchas          #+#    #+#             */
/*   Updated: 2019/11/15 19:57:11 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/mod1.hpp"

cl_program		ft_cl_program(cl_context c, char *file_name)
{
	FILE		*fp;
	char		*content;
	size_t		file_size;
	cl_int		ret;
	cl_program	program;

	content = (char *)malloc(sizeof(char) * MAX_SOURCE_SIZE);
	assert(fp = fopen(file_name, "r"));
	file_size = fread(content, 1, MAX_SOURCE_SIZE, fp);
	program	= clCreateProgramWithSource(c, 1, (const char **)&content,
			(const size_t *)&file_size, &ret);
	assert(ret == CL_SUCCESS);
	free(content), content = NULL;
	fclose(fp);
	return (program);
}

cl_platform_id	ft_cl_platform(void)
{
	cl_platform_id		platform_id;
	cl_int				ret;
	cl_uint				platform_num;

	ret = clGetPlatformIDs(1, &platform_id, &platform_num);
	assert (ret == CL_SUCCESS && platform_num);
	return (platform_id);
}

cl_device_id	ft_cl_device(cl_platform_id platform_id)
{
	cl_device_id	device_id;
	cl_int			ret;
	cl_uint			device_num;

	ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, 1, &device_id, &device_num);
//	ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_CPU, 1, &device_id, &device_num);
	assert (ret == CL_SUCCESS && device_num);
	return (device_id);
}


cl_context		ft_cl_context(cl_device_id *device_id)
{
	cl_context	context;
	cl_int		ret;

	context = clCreateContext(NULL, 1, device_id, NULL, NULL, &ret);
	assert (ret == CL_SUCCESS);
	return (context);
}

cl_command_queue	ft_cl_command_queue(cl_context context, cl_device_id device_id)
{
	cl_command_queue	command_queue;
	cl_int				ret;

	command_queue = clCreateCommandQueue(context, device_id, 0, &ret);
	assert (ret == CL_SUCCESS);
	return (command_queue);
}
