/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 18:06:44 by ebatchas          #+#    #+#             */
/*   Updated: 2019/11/02 13:09:12 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.hpp"

class	Camera
{
public:
	float		yaw;
	float		pitch;
	float		sensitivity;
	float		speed;
	float		zoom;
	float		asp_ratio;
	glm::vec3	pos;
	glm::vec3	at;
	glm::vec3	up;
	glm::vec3	u;
	glm::vec3	rt;

	glm::mat4	projection;
	glm::mat4	view;

	Camera();
	Camera(glm::vec3 pos, glm::vec3 at);
	void	process_camera(Input in, float delta);
	void	update_camera_vecs(void);
	void	update_camera_mats(void);
	void	camera_on_mouse_move(float xoffset, float yoffset, float delta_time);
	void	camera_on_mouse_wheel(float yoffset, float delta_time);
	void	camera_on_keyboard(Input in, float delta_time);
	~Camera(){};
};
