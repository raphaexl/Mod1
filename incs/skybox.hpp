/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 02:06:24 by ebatchas          #+#    #+#             */
/*   Updated: 2019/11/02 13:10:46 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.hpp"

class	Skybox
{
	public:
		std::vector<Image>	faces;
		GLuint		vao;
		GLuint		vbo;
		GLuint		texture;
		glm::vec3	vertices[36];
		Shader		shader;
		Skybox();
		Skybox(std::string face1, std::string face2, std::string face3, std::string face4,
				std::string face5, std::string face6);
		void	Load(std::string face1, std::string face2, std::string face3, std::string face4,
				std::string face5, std::string face6);
		void	Load(void);
		void	Display(void);
		~Skybox();
};
