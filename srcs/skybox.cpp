/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 02:14:10 by ebatchas          #+#    #+#             */
/*   Updated: 2019/11/02 16:14:58 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/mod1.hpp"

Skybox::Skybox()
{
	this->vertices[0] = glm::vec3(-1.0f,  1.0f, -1.0f);
	this->vertices[1] = glm::vec3(-1.0f, -1.0f, -1.0f);
	this->vertices[2] = glm::vec3(1.0f, -1.0f, -1.0f);
	this->vertices[3] = glm::vec3(1.0f, -1.0f, -1.0f);
	this->vertices[4] = glm::vec3(1.0f,  1.0f, -1.0f);
	this->vertices[5] = glm::vec3(-1.0f,  1.0f, -1.0f);
	this->vertices[6] = glm::vec3(-1.0f, -1.0f,  1.0f);
	this->vertices[7] = glm::vec3(-1.0f, -1.0f, -1.0f);
	this->vertices[8] = glm::vec3(-1.0f,  1.0f, -1.0f);
	this->vertices[9] = glm::vec3(-1.0f,  1.0f, -1.0f);
	this->vertices[10] = glm::vec3(-1.0f,  1.0f,  1.0f);
	this->vertices[11] = glm::vec3(-1.0f, -1.0f,  1.0f);
	this->vertices[12] = glm::vec3(1.0f, -1.0f, -1.0f);
	this->vertices[13] = glm::vec3(1.0f, -1.0f,  1.0f);
	this->vertices[14] = glm::vec3(1.0f,  1.0f,  1.0f);
	this->vertices[15] = glm::vec3(1.0f,  1.0f,  1.0f);
	this->vertices[16] = glm::vec3(1.0f,  1.0f, -1.0f);
	this->vertices[17] = glm::vec3(1.0f, -1.0f, -1.0f);
	this->vertices[18] = glm::vec3(-1.0f, -1.0f,  1.0f);
	this->vertices[19] = glm::vec3(-1.0f,  1.0f,  1.0f);
	this->vertices[20] = glm::vec3(1.0f,  1.0f,  1.0f);
	this->vertices[21] = glm::vec3(1.0f,  1.0f,  1.0f);
	this->vertices[22] = glm::vec3(1.0f, -1.0f,  1.0f);
	this->vertices[23] = glm::vec3(-1.0f, -1.0f,  1.0f);
	this->vertices[24] = glm::vec3(-1.0f,  1.0f, -1.0f);
	this->vertices[25] = glm::vec3(1.0f,  1.0f, -1.0f);
	this->vertices[26] = glm::vec3(1.0f,  1.0f,  1.0f);
	this->vertices[27] = glm::vec3(1.0f,  1.0f,  1.0f);
	this->vertices[28] = glm::vec3(-1.0f,  1.0f,  1.0f);
	this->vertices[29] = glm::vec3(-1.0f,  1.0f, -1.0f);
	this->vertices[30] = glm::vec3(-1.0f, -1.0f, -1.0f);
	this->vertices[31] = glm::vec3(-1.0f, -1.0f,  1.0f);
	this->vertices[32] = glm::vec3(1.0f, -1.0f, -1.0f);
	this->vertices[33] = glm::vec3(1.0f, -1.0f, -1.0f);
	this->vertices[34] = glm::vec3(-1.0f, -1.0f,  1.0f);
	this->vertices[35] = glm::vec3(1.0f, -1.0f,  1.0f);
	this->vao = 0;
	this->vbo = 0;
	this->texture = 0;
	this->faces.reserve(6);
	this->faces.push_back(Image(SKYBOX_RIGHT_IMG));
	this->faces.push_back(Image(SKYBOX_LEFT_IMG));
	this->faces.push_back(Image(SKYBOX_TOP_IMG));
	this->faces.push_back(Image(SKYBOX_BOTTOM_IMG));
	this->faces.push_back(Image(SKYBOX_FRONT_IMG));
	this->faces.push_back(Image(SKYBOX_BACK_IMG));
}

Skybox::Skybox(std::string face1, std::string face2, std::string face3,
		std::string face4, std::string face5, std::string face6)
{
	this->vertices[0] = glm::vec3(-1.0f,  1.0f, -1.0f);
	this->vertices[1] = glm::vec3(-1.0f, -1.0f, -1.0f);
	this->vertices[2] = glm::vec3(1.0f, -1.0f, -1.0f);
	this->vertices[3] = glm::vec3(1.0f, -1.0f, -1.0f);
	this->vertices[4] = glm::vec3(1.0f,  1.0f, -1.0f);
	this->vertices[5] = glm::vec3(-1.0f,  1.0f, -1.0f);
	this->vertices[6] = glm::vec3(-1.0f, -1.0f,  1.0f);
	this->vertices[7] = glm::vec3(-1.0f, -1.0f, -1.0f);
	this->vertices[8] = glm::vec3(-1.0f,  1.0f, -1.0f);
	this->vertices[9] = glm::vec3(-1.0f,  1.0f, -1.0f);
	this->vertices[10] = glm::vec3(-1.0f,  1.0f,  1.0f);
	this->vertices[11] = glm::vec3(-1.0f, -1.0f,  1.0f);
	this->vertices[12] = glm::vec3(1.0f, -1.0f, -1.0f);
	this->vertices[13] = glm::vec3(1.0f, -1.0f,  1.0f);
	this->vertices[14] = glm::vec3(1.0f,  1.0f,  1.0f);
	this->vertices[15] = glm::vec3(1.0f,  1.0f,  1.0f);
	this->vertices[16] = glm::vec3(1.0f,  1.0f, -1.0f);
	this->vertices[17] = glm::vec3(1.0f, -1.0f, -1.0f);
	this->vertices[18] = glm::vec3(-1.0f, -1.0f,  1.0f);
	this->vertices[19] = glm::vec3(-1.0f,  1.0f,  1.0f);
	this->vertices[20] = glm::vec3(1.0f,  1.0f,  1.0f);
	this->vertices[21] = glm::vec3(1.0f,  1.0f,  1.0f);
	this->vertices[22] = glm::vec3(1.0f, -1.0f,  1.0f);
	this->vertices[23] = glm::vec3(-1.0f, -1.0f,  1.0f);
	this->vertices[24] = glm::vec3(-1.0f,  1.0f, -1.0f);
	this->vertices[25] = glm::vec3(1.0f,  1.0f, -1.0f);
	this->vertices[26] = glm::vec3(1.0f,  1.0f,  1.0f);
	this->vertices[27] = glm::vec3(1.0f,  1.0f,  1.0f);
	this->vertices[28] = glm::vec3(-1.0f,  1.0f,  1.0f);
	this->vertices[29] = glm::vec3(-1.0f,  1.0f, -1.0f);
	this->vertices[30] = glm::vec3(-1.0f, -1.0f, -1.0f);
	this->vertices[31] = glm::vec3(-1.0f, -1.0f,  1.0f);
	this->vertices[32] = glm::vec3(1.0f, -1.0f, -1.0f);
	this->vertices[33] = glm::vec3(1.0f, -1.0f, -1.0f);
	this->vertices[34] = glm::vec3(-1.0f, -1.0f,  1.0f);
	this->vertices[35] = glm::vec3(1.0f, -1.0f,  1.0f);
	this->vao = 0;
	this->vbo = 0;
	this->texture = 0;
	this->faces.reserve(6);
	this->faces.push_back(Image(face1));
	this->faces.push_back(Image(face2));
	this->faces.push_back(Image(face3));
	this->faces.push_back(Image(face4));
	this->faces.push_back(Image(face5));
	this->faces.push_back(Image(face6));
}

void	Skybox::Load(std::string face1, std::string face2, std::string face3,
		std::string face4, std::string face5, std::string face6)
{
	this->faces.reserve(6);
	this->faces.push_back(Image(face1));
	this->faces.push_back(Image(face2));
	this->faces.push_back(Image(face3));
	this->faces.push_back(Image(face4));
	this->faces.push_back(Image(face5));
	this->faces.push_back(Image(face6));
	Load();
}

void	Skybox::Load(void)
{
	for (std::vector<Image>::iterator it = this->faces.begin(); it != this->faces.end(); it++)
	{
		it->Load();
	}
	glGenVertexArrays(1, &this->vao);
	glBindVertexArray(this->vao);
	glGenBuffers(1, &this->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(glm::vec3), this->vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glGenTextures(1, &this->texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->texture);
	for (unsigned int i{0}; i < this->faces.size(); i++)
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, faces[i].internal_format, faces[i].width,
				faces[i].height, 0, faces[i].format, faces[i].type, faces[i].data);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	this->shader = Shader("commons/skybox_v_shader.glsl", "commons/skybox_f_shader.glsl");
	this->shader.Load();
	this->shader.Use();
}

void	Skybox::Display(void)
{
	glBindVertexArray(this->vao);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->texture);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

Skybox::~Skybox()
{
	glDeleteTextures(1, &this->texture);
	glDeleteBuffers(1, &this->vbo);
	glDeleteVertexArrays(1, &this->vao);
}
