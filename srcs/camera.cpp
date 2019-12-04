/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 18:12:49 by ebatchas          #+#    #+#             */
/*   Updated: 2019/12/04 14:35:56 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/mod1.hpp"

Camera::Camera()
{
	this->pos = glm::vec3(0.0, 0.0, 5.0);
	this->at = glm::vec3(0.0, 0.0, 0.0);
	this->up = glm::vec3(0.0, 1.0, 0.0);
	this->u = up;
	this->yaw = YAW;
	this->pitch = PITCH;
	this->sensitivity = SENSITIVITY;
	this->zoom = ZOOM;
	this->speed = SPEED;
	update_camera_vecs();
	this->view = glm::mat4(1.0f);
	this->projection = glm::mat4(1.0f);
	this->asp_ratio = float(W_W) / float(W_H);
}

Camera::Camera(glm::vec3 pos, glm::vec3 at)
{
	this->pos = pos;
	this->at = at;
	this->up = glm::vec3(0.0, 1.0, 0.0);
	this->u = up;
	this->yaw = YAW;
	this->pitch = PITCH;
	this->sensitivity = SENSITIVITY;
	this->zoom = ZOOM;
	this->speed = SPEED;
	update_camera_vecs();
	this->view = glm::mat4(1.0f);
	this->projection = glm::mat4(1.0f);
	this->asp_ratio = float(W_W) / float(W_H);
}

void	Camera::update_camera_vecs(void)
{
	glm::vec3 at;

	at.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	at.y = sin(glm::radians(this->pitch));
	at.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	this->at = glm::normalize(at);
	this->rt = glm::normalize(glm::cross(this->at, this->up));
	this->u = glm::normalize(glm::cross(this->rt, this->at));
}

void	Camera::update_camera_mats(void)
{
	this->view = glm::lookAt(this->pos, this->pos + this->at, this->u);
	this->projection = glm::perspective(this->zoom, this->asp_ratio, 0.1f, 1000.0f);
}

void	Camera::camera_on_mouse_move(float xoffset, float yoffset, float delta_time)
{
	xoffset *= this->sensitivity * delta_time;
	yoffset *= this->sensitivity * delta_time;

	this->yaw += xoffset;
	this->pitch += yoffset;
	if (this->pitch > 89.0f)
		this->pitch = 89.0f;
	if (this->pitch < -89.0f)
		this->pitch = -89.0f;
	update_camera_vecs();
}


void	Camera::camera_on_mouse_wheel(float yoffset, float delta_time)
{
	yoffset *= delta_time;
	if (this->zoom > 1.0f && this->zoom < 45.0f)
		this->zoom -= yoffset;
	else if (this->zoom <= 1.0f)
		this->zoom = 1.0f;
	else if (this->zoom >= 45.0f)
		this->zoom = 45.0f;
}

void	Camera::camera_on_keyboard(Input in, float delta_time)
{
	if (in.keys[SDL_SCANCODE_UP])
		this->pos += this->at * delta_time * this->speed;
	else if (in.keys[SDL_SCANCODE_DOWN])
		this->pos -= this->at * delta_time * this->speed;
	else if (in.keys[SDL_SCANCODE_LEFT])
		this->pos += this->rt * delta_time * this->speed;
	else if (in.keys[SDL_SCANCODE_RIGHT])
		this->pos -= this->rt * delta_time * this->speed;
}

void	Camera::process_camera(Input in, float delta_time)
{
	camera_on_keyboard(in, delta_time);
	if (in.mouse[SDL_BUTTON_RIGHT])
		camera_on_mouse_move(in.mouse_xrel, in.mouse_yrel, delta_time);
	camera_on_mouse_wheel(in.mouse_ywheel, delta_time);
	this->update_camera_mats();
}
