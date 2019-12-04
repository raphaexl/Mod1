/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terrain.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:42:54 by ebatchas          #+#    #+#             */
/*   Updated: 2019/12/04 13:54:13 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/mod1.hpp"

Terrain::Terrain()
{
	this->size = DEFAULT_TERRAIN_SIZE;
	this->vao = 0;
	this->v_vbo = 0;
	this->uv_vbo = 0;
	this->n_vbo = 0;
	this->v_ebo = 0;
	this->texture = 0;
	this->rotate = glm::mat4(1.0f);
	this->scale = glm::mat4(1.0f);
	this->translate = glm::mat4(1.0f);
	this->model = glm::mat4(1.0f);
	this->texture = 0;
	this->v_scale = (this->size - 1) * 1000.0 / 20.0;
		this->max_height = -1;
}

Terrain::Terrain(int	size, Map map)
{

	this->size = 0;
	this->vao = 0;
	this->v_vbo = 0;
	this->uv_vbo = 0;
	this->n_vbo = 0;
	this->v_ebo = 0;
	this->texture = 0;
	this->size = size;
	this->map = map;
	this->Gride(size);
	this->rotate = glm::mat4(1.0f);
	this->scale = glm::mat4(1.0f);
	this->translate = glm::mat4(1.0f);
	this->model = glm::mat4(1.0f);
	this->texture = 0;
	this->v_scale = (this->size - 1) * 1000.0 / 20.0;
		this->max_height = -1;
}

void	Terrain::Gride(int size)
{
		this->size = size;
	int		num_vertices = size * size;

	this->v_scale = (this->size - 1) / (1000.0 * 20.0);
	this->vertices.resize(num_vertices);
	this->normals.resize(num_vertices);
	this->uvs.resize(num_vertices);
	this->height.resize(num_vertices);

	float		width = (size - 1);
	float		height = (size - 1);
	float		h_width = width * 0.5;
	float		h_height = height * 0.5;

	float radius = 10.0;
	unsigned int m_size = this->map.data.size();

	for (unsigned int k{0}; k <m_size; k++)
	{
		glm::vec3 v = this->map.data[k];
		this->map.data[k] = glm::vec3(v_scale * v.x, v_scale * v.y, v.z);
	}
	for (unsigned int k{0}; k <m_size ; k++)
	for (int j{0}; j < size ; j++)
	{
		for (int i{0}; i < size ; i++)
		{
			{
				glm::vec3 v = this->map.data[k];
				float	x =  v.x;
				float	y =  v.y;
		if (i == 1 || j == 1 || i == size - 1 || j == size - 1)
		{
			this->map.data.push_back(glm::vec3(i, j, 0.0));
			continue;
		}
				if (int(x) - 1 == i && int(y) - 1 == j)
				{
					//std::cout<<"In fact : x = "<<x<<" and y = "<<y<<std::endl;
					continue;
				}
				float	dist = distance(i, j, x, y);
				if (dist < radius)
				this->map.data.push_back(glm::vec3(i, j, v.z - dist*10.0));
				//this->map.data.push_back(glm::vec3(i * 1000.0, j * 1000.0, v.z - 100));//dist*10.0));
			}
		}
	}
	std::cout<<"Now Size is : "<<this->map.data.size()<<std::endl;
	for (int j{0}; j < size; j++)
	{
		for (int i{0}; i < size; i++)
		{
			unsigned int index = j * size + i;

			glm::vec3	vertex;
			float		s = float(i) / float(size - 1);
			float		t = float(j) / float(size - 1);

			this->normals[index] = glm::vec3(0.0f);
			this->uvs[index] = glm::vec2(s, t);

			vertex = glm::vec3(s * width - h_width, 0.0, t * height - h_height);
//The Algorithm
			float	sum_Num = 0.0;
			float	sum_Den = 1.0;
			float	d;

			for (unsigned int k{0}; k < this->map.data.size(); k++)
			{
				glm::vec3 v = this->map.data[k];
				float	z = v.z * this->v_scale;
				float	x = ((v.x - 1.0) / width) * width - h_width;
				float	y = ((v.y - 1.0) / height) * height - h_height;
				d = distance(vertex.x, vertex.z, x, y);
				if (d <= 0.1f)
				{
					d = 0.1f;
					continue;
				}
				sum_Num += (z / (pow(d, 2.0)));
				sum_Den += (1.0f / (pow(d, 2.0)));
			}
			this->height[index] = vertex.y = (sum_Num / sum_Den);
					// Real this->height[index] = vertex.y = sum_Num / sum_Den;
			if (this->max_height < vertex.y)
				this->max_height = vertex.y;
			this->vertices[index] = vertex;
		}
	}
	std::cout<<"The max height is "<<max_height<<std::endl;
	this->v_indices.resize(((size - 1) * (size - 1) * 2) * 3);
	unsigned int index = 0;
	for (int j{0}; j < size - 1; j++)
	{
		for (int i{0}; i < size - 1; i++)
		{
			unsigned int v_index = j * size + i;

			this->v_indices[index++] = v_index;
			this->v_indices[index++] = v_index + size + 1;
			this->v_indices[index++] = v_index + 1;
			this->v_indices[index++] = v_index;
			this->v_indices[index++] = v_index + size;
			this->v_indices[index++] = v_index + size + 1;
		}
	}
	for (unsigned int i{0}; i < this->v_indices.size(); i+=3)
	{
		glm::vec3 v0 = this->vertices[v_indices[i + 0]];
		glm::vec3 v1 = this->vertices[v_indices[i + 1]];
		glm::vec3 v2 = this->vertices[v_indices[i + 2]];

		glm::vec3 normal = glm::normalize(glm::cross(v1 - v0, v2 - v0));
		this->normals[v_indices[i + 0]] = normal;
		this->normals[v_indices[i + 1]] = normal;
		this->normals[v_indices[i + 2]] = normal;
	}
	this->Height();
	std::cout<<"vertices size : "<<this->vertices.size()<<std::endl;
	std::cout<<"vertices indices size : "<<this->v_indices.size()<<std::endl;
}

void	Terrain::Generate(int size, Map map)
{
	this->size = size;
	this->v_scale = (this->size - 1) / (1000.0 * 20.0);
	this->map = map;
	this->Gride(size);
	this->Load();
}


void	Terrain::Height(void)
{
}

void	Terrain::Load(int size, Map map)
{
	this->map = map;
	this->Gride(size);
	this->Load();
}

void	Terrain::ProcessInput(Input in, float delta_time)
{
	static	float	scale = 1.0f;
	float			deltax{delta_time * in.mouse_xrel};
	float			deltay{delta_time * in.mouse_yrel};

	scale += (in.mouse_ywheel * delta_time);
	this->scale = glm::scale(glm::mat4(1.0f), glm::vec3(scale, scale, scale));
	if (in.mouse[SDL_BUTTON_LEFT])
	{
		this->rotate = glm::rotate(this->rotate, deltax, glm::vec3(0.0, 1.0, 0.0));
		this->rotate = glm::rotate(this->rotate, deltay, glm::vec3(1.0, 0.0, 0.0));
	}
	else if (in.mouse[SDL_BUTTON_RIGHT])
		this->translate = glm::translate(this->translate, glm::vec3(deltax, -deltay, 0.0));
	this->model = this->translate * this->rotate * this->scale;
}

void	Terrain::Load(void)
{
	glGenBuffers(1, &this->v_vbo);
	glGenBuffers(1, &this->uv_vbo);
	glGenBuffers(1, &this->n_vbo);
	glGenBuffers(1, &this->v_ebo);
	glGenVertexArrays(1, &this->vao);
	glBindVertexArray(this->vao);
	glBindBuffer(GL_ARRAY_BUFFER, this->v_vbo);
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(glm::vec3), &this->vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, this->uv_vbo);
	glBufferData(GL_ARRAY_BUFFER, this->uvs.size() *  sizeof(glm::vec2), &this->uvs[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, this->n_vbo);
	glBufferData(GL_ARRAY_BUFFER, this->normals.size() * sizeof(glm::vec3), &this->normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->v_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, v_indices.size() * sizeof(unsigned int),  &this->v_indices[0], GL_STATIC_DRAW);
	glBindVertexArray(0);
	Image image = Image("data/imgs/terrain/terrain.jpg");
	image.Load();
	glGenTextures(1, &this->texture);
	glBindTexture(GL_TEXTURE_2D, this->texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, image.internal_format, image.width, image.height, 0, image.format, image.type, image.data);
	glGenerateMipmap(GL_TEXTURE_2D);
	this->shader = Shader("commons/terrain_v_shader.glsl", "commons/terrain_f_shader.glsl");
	this->shader.Load();
	this->shader.Use();
}

void	Terrain::Display(void)
{
	glBindVertexArray(this->vao);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->texture);
	//	glDrawElements(GL_LINE_STRIP, this->v_indices.size(), GL_UNSIGNED_INT, 0);
	glDrawElements(GL_TRIANGLES, this->v_indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

Terrain::~Terrain()
{
	glDeleteBuffers(1, &this->v_vbo);
	glDeleteBuffers(1, &this->uv_vbo);
	glDeleteBuffers(1, &this->n_vbo);
	glDeleteBuffers(1, &this->v_ebo);
	glDeleteVertexArrays(1, &this->vao);
}
