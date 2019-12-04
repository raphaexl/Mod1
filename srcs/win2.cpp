/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 15:30:34 by ebatchas          #+#    #+#             */
/*   Updated: 2019/11/17 17:21:05 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/mod1.hpp"

Mwindow::Mwindow(const char	*file_name)
{
	this->map.Load(file_name);
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr<<"Error SDL_Init()" <<SDL_GetError()<<std::endl;
		exit(EXIT_FAILURE);
	}
	if ((IMG_Init(IMG_INIT_FLAGS) & IMG_INIT_FLAGS) != IMG_INIT_FLAGS)
	{
		std::cerr<<"Error IMG_Init()" <<IMG_GetError()<<std::endl;
		exit(EXIT_FAILURE);
	}
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	if (!(window = SDL_CreateWindow(W_TITLE, SDL_WINDOWPOS_UNDEFINED,
					SDL_WINDOWPOS_UNDEFINED, W_W, W_H, SDL_WINDOW_SHOWN |
					SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE)))
	{
		std::cerr<<"Error SDL_CreateWindow()" <<SDL_GetError()<<std::endl;
		exit(EXIT_FAILURE);
	}
	if (!(context = SDL_GL_CreateContext(window)))
	{
		std::cerr<<"Error SDL_CreateContext()" <<SDL_GetError()<<std::endl;
		exit(EXIT_FAILURE);
	}
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr<<"Error glewInit() Failed"<<std::endl;
		SDL_GL_DeleteContext(context);
		SDL_DestroyWindow(window);
		exit(EXIT_FAILURE);
	}
	SDL_GL_SetSwapInterval(1);
	glEnable(GL_DEPTH_TEST);
}

void	Mwindow::process_input(void)
{
	t_opencl	opencl;
	Input		input;
	Cube		cube = Cube();
	Cube		water = Cube();
	Camera		camera = Camera(glm::vec3(0.0, 1.8, 10.0), glm::vec3(0.0, 0.0, -1.0));
	Skybox		skybox = Skybox();
	Terrain		terrain = Terrain();
	SPH			sph = SPH();
	Uint32		last_time;
	Uint32		curr_time;
	int			w(0), h(0);
	float		delta_time{0.01f};

	ft_opencl_init(&opencl, (char *)std::string("kernels/sph.cl").c_str());
	memset(&input, SDL_FALSE, sizeof(Input));
	terrain.Load(19, this->map);
	cube.Load();
	water.Load();
	skybox.Load();
	last_time = SDL_GetTicks();
	sph.InitSPH();
	sph.terrain = terrain.height;
	//ft_opencl_mem(&opencl, &sph);
	//	ft_opencl_kernel(&opencl, &sph);
	//exit(-1);
	while (not input.quit)
	{
		input.update();
		camera.process_camera(input, delta_time);
		terrain.ProcessInput(input, delta_time);
		//ft_opencl_run(&opencl, &sph);
		sph.Update();
		glClearColor(0.02, 0.02, 0.02, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glDepthMask(GL_FALSE);
		skybox.shader.Use();
		glm::mat4 M = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(glm::mat3(camera.view));
		glm::mat4 projection = camera.projection;
		M = glm::scale(M, glm::vec3(15.0, 15.0, 15.0));
		skybox.shader.set_mat4("V", view);
		skybox.shader.set_mat4("P", projection);
		skybox.shader.set_mat4("M", M);
		skybox.Display();
		glDepthMask(GL_TRUE);

/*
 * The BOX
		cube.shader.Use();
		cube.shader.set_mat4("view", camera.view);
		cube.shader.set_mat4("projection", camera.projection);
		cube.shader.set_vec3("cam_pos", camera.pos);
		cube.shader.set_int("indice", 1);
		glm::mat4 model1 = glm::mat4(1.0f);
		float scale = 1.0;
//		model1 = glm::translate(model1, glm::vec3(0.0, scale / 2.0 - 0.5, 0.0));
		model1 = glm::scale(model1, glm::vec3(scale, scale, scale));
		cube.shader.set_mat4("model", terrain.model * model1);
		cube.Display();*/
		
		water.shader.Use();
		water.shader.set_mat4("view", camera.view);
		water.shader.set_mat4("projection", camera.projection);
		water.shader.set_vec3("cam_pos", camera.pos);
		water.shader.set_int("indice", 2);
//	int i (0);
		//for(auto p__pos : sph.pos)
		for(size_t i{0}; i < sph.particles.size(); i++)
		{
			
			cl_float3 p_pos = {{sph.particles[i].pos.x, sph.particles[i].pos.y,sph.particles[i].pos.z}};
		//	i++;
			glm::mat4 model1 = glm::mat4(1.0f);
			float	scale = 1.0;//16.0;
			model1 = glm::scale(model1, glm::vec3(scale, scale, scale));
			scale = 1.0 / 16.0;
			glm::vec3 pos = scale * glm::vec3(p_pos.s[0],  p_pos.s[1], p_pos.s[2]);
			model1 = glm::translate(model1, pos);
			water.shader.set_mat4("model", terrain.model * model1);
			water.Display();
		}
	//	std::cout<<"size is : "<<i<<std::endl;
		//	model = glm::rotate(model, float(SDL_GetTicks()/1000.0f), glm::vec3(0.0, 1.0, 0.0));
		terrain.shader.Use();
		terrain.shader.set_mat4("view", camera.view);
		terrain.shader.set_mat4("projection", camera.projection);
		terrain.shader.set_vec3("cam_pos", camera.pos);
		terrain.shader.set_mat4("model", terrain.model);
	//	terrain.Display();
		curr_time = SDL_GetTicks();
		delta_time = (curr_time - last_time) / 1000.0f;
		last_time = curr_time;
		glUseProgram(0);
		SDL_GetWindowSize(this->window, &w, &h);
		if (!w || !h)
			;
		else
		{
			glViewport(0, 0, w, h);
			camera.asp_ratio = float(w) / float(h);
		}
		SDL_GL_SwapWindow(this->window);
	}
	//ft_opencl_quit(&opencl);
}

Mwindow::~Mwindow()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
};
