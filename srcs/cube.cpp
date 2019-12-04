/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 17:36:45 by ebatchas          #+#    #+#             */
/*   Updated: 2019/10/30 18:05:45 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/mod1.hpp"

Cube::Cube()
{
	this->vertices[0] = glm::vec3(-0.5f, -0.5f, -0.5f);
	this->vertices[1] = glm::vec3(0.5f, -0.5f, -0.5f);
	this->vertices[2] = glm::vec3(0.5f,  0.5f, -0.5f);
	this->vertices[3] =  glm::vec3(0.5f,  0.5f, -0.5f);
	this->vertices[4] = glm::vec3(-0.5f,  0.5f, -0.5f);
	this->vertices[5] = glm::vec3(-0.5f, -0.5f, -0.5f);
	this->vertices[6] = glm::vec3(-0.5f, -0.5f,  0.5f);
	this->vertices[7] = glm::vec3(0.5f, -0.5f,  0.5f);
	this->vertices[8] = glm::vec3(0.5f,  0.5f,  0.5f);
	this->vertices[9] = glm::vec3(0.5f,  0.5f,  0.5f);
	this->vertices[10] = glm::vec3(-0.5f,  0.5f,  0.5f);
	this->vertices[11] = glm::vec3(-0.5f, -0.5f,  0.5f);
	this->vertices[12] = glm::vec3(-0.5f,  0.5f,  0.5f);
	this->vertices[13] = glm::vec3(-0.5f,  0.5f, -0.5f);
	this->vertices[14] = glm::vec3(-0.5f, -0.5f, -0.5f);
	this->vertices[15] = glm::vec3(-0.5f, -0.5f, -0.5f);
	this->vertices[16] = glm::vec3(-0.5f, -0.5f,  0.5f);
	this->vertices[17] = glm::vec3(-0.5f,  0.5f,  0.5f);
	this->vertices[18] = glm::vec3(0.5f,  0.5f,  0.5f);
	this->vertices[19] = glm::vec3(0.5f,  0.5f, -0.5f);
	this->vertices[20] = glm::vec3(0.5f, -0.5f, -0.5f);
	this->vertices[21] = glm::vec3(0.5f, -0.5f, -0.5f);
	this->vertices[22] = glm::vec3(0.5f, -0.5f,  0.5f);
	this->vertices[23] = glm::vec3(0.5f,  0.5f,  0.5f);
	this->vertices[24] = glm::vec3(-0.5f, -0.5f, -0.5f);
	this->vertices[25] = glm::vec3(0.5f, -0.5f, -0.5f);
	this->vertices[26] = glm::vec3(0.5f, -0.5f,  0.5f);
	this->vertices[27] = glm::vec3(0.5f, -0.5f,  0.5f);
	this->vertices[28] = glm::vec3(-0.5f, -0.5f,  0.5f);
	this->vertices[29] = glm::vec3(-0.5f, -0.5f, -0.5f);
	this->vertices[30] = glm::vec3(-0.5f,  0.5f, -0.5f);
	this->vertices[31] = glm::vec3(0.5f,  0.5f, -0.5f);
	this->vertices[32] = glm::vec3(0.5f,  0.5f,  0.5f);
	this->vertices[33] = glm::vec3(0.5f,  0.5f,  0.5f);
	this->vertices[34] = glm::vec3(-0.5f,  0.5f,  0.5f);
	this->vertices[35] = glm::vec3(-0.5f,  0.5f, -0.5f);
	
	this->normals[0] = glm::vec3(0.0f,  0.0f, -1.0f);
	this->normals[1] = glm::vec3(0.0f,  0.0f, -1.0f);
	this->normals[2] = glm::vec3(0.0f,  0.0f, -1.0f);
	this->normals[3] = glm::vec3(0.0f,  0.0f, -1.0f);
	this->normals[4] = glm::vec3(0.0f,  0.0f, -1.0f);
	this->normals[5] = glm::vec3(0.0f,  0.0f, -1.0f);
	this->normals[6] = glm::vec3(0.0f,  0.0f, 1.0f);
	this->normals[7] = glm::vec3(0.0f,  0.0f, 1.0f);
	this->normals[8] = glm::vec3(0.0f,  0.0f, 1.0f);
	this->normals[9] = glm::vec3(0.0f,  0.0f, 1.0f);
	this->normals[10] = glm::vec3(0.0f,  0.0f, 1.0f);
	this->normals[11] = glm::vec3(0.0f,  0.0f, 1.0f);
	this->normals[12] = glm::vec3(-1.0f,  0.0f,  0.0f);
	this->normals[13] = glm::vec3(-1.0f,  0.0f,  0.0f);
	this->normals[14] = glm::vec3(-1.0f,  0.0f,  0.0f);
	this->normals[15] = glm::vec3(-1.0f,  0.0f,  0.0f);
	this->normals[16] = glm::vec3(-1.0f,  0.0f,  0.0f);
	this->normals[17] = glm::vec3(-1.0f,  0.0f,  0.0f);
	this->normals[18] = glm::vec3(1.0f,  0.0f,  0.0f);
	this->normals[19] = glm::vec3(1.0f,  0.0f,  0.0f);
	this->normals[20] = glm::vec3(1.0f,  0.0f,  0.0f);
	this->normals[21] = glm::vec3(1.0f,  0.0f,  0.0f);
	this->normals[22] = glm::vec3(1.0f,  0.0f,  0.0f);
	this->normals[23] = glm::vec3(1.0f,  0.0f,  0.0f);
	this->normals[24] = glm::vec3(0.0f, -1.0f,  0.0f);
	this->normals[25] = glm::vec3(0.0f, -1.0f,  0.0f);
	this->normals[26] = glm::vec3(0.0f, -1.0f,  0.0f);
	this->normals[27] = glm::vec3(0.0f, -1.0f,  0.0f);
	this->normals[28] = glm::vec3(0.0f, -1.0f,  0.0f);
	this->normals[29] = glm::vec3(0.0f, -1.0f,  0.0f);
	this->normals[30] = glm::vec3(0.0f,  1.0f,  0.0f);
	this->normals[31] = glm::vec3(0.0f,  1.0f,  0.0f);
	this->normals[32] = glm::vec3(0.0f,  1.0f,  0.0f);
	this->normals[33] = glm::vec3(0.0f,  1.0f,  0.0f);
	this->normals[34] = glm::vec3(0.0f,  1.0f,  0.0f);
	this->normals[35] = glm::vec3(0.0f,  1.0f,  0.0f);
	
	this->vao = 0;
	this->vbo = 0;
}

void	Cube::Load(void)
{
	glGenBuffers(1, &this->vbo);
	glGenBuffers(1, &this->n_vbo);
	glGenVertexArrays(1, &this->vao);
	glBindVertexArray(this->vao);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(glm::vec3), &this->vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)NULL);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, this->n_vbo);
	glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(glm::vec3), &this->normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)NULL);
	glEnableVertexAttribArray(1);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	this->shader = Shader("commons/cube_v_shader.glsl", "commons/cube_f_shader.glsl");
	this->shader.Load();
	this->shader.Use();
}


void	Cube::Display(void)
{
	glBindVertexArray(this->vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

}

Cube::~Cube()
{
	glDeleteBuffers(1, &this->vbo);
	glDeleteBuffers(1, &this->n_vbo);
	glDeleteVertexArrays(1, &this->vao);
}
