/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 17:31:41 by ebatchas          #+#    #+#             */
/*   Updated: 2019/11/12 18:56:36 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shader.hpp"

class Cube
{
	private:
		glm::vec3	vertices[36];
		glm::vec3	normals[36];
		GLuint		vbo;
		GLuint		vao;
		GLuint		n_vbo;
		
	public:
		Shader		shader;
		Cube();
		void	Load(void);
		void	Display(void);
		~Cube();
};
