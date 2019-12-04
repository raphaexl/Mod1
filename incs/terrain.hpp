/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terrain.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:36:18 by ebatchas          #+#    #+#             */
/*   Updated: 2019/12/04 13:55:03 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
# include "skybox.hpp"

class	Terrain
{
	public:
		int							size;
		float						max_height;
		float						v_scale;
		std::vector<float>			height;
		Map							map;
		GLuint						v_vbo;
		GLuint						n_vbo;
		GLuint						uv_vbo;
		GLuint						v_ebo;
		GLuint						vao;
		GLuint						texture;
		std::vector<glm::vec3>		vertices;
		std::vector<glm::vec3>		normals;
		std::vector<glm::vec2>		uvs;
		std::vector<unsigned int>	v_indices;
		glm::mat4					rotate;
		glm::mat4					translate;
		glm::mat4					scale;
		glm::mat4					model;
		Shader						shader;
		Terrain();
		Terrain(int size, Map map);
		void	Generate(int size, Map map);
		void	Gride(int size);
		void	Load(void);
		void	Load(int size, Map map);
		void	Height(void);
		void	ProcessInput(Input in, float delta_time);
		void	Display(void);
		~Terrain();

		inline	float	distance(float xo, float yo, float x, float y)
		{
			return (sqrt((xo - x) * (xo - x) + (yo - y) * (yo - y)));
		}

};
