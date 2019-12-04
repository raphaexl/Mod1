/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 18:33:57 by ebatchas          #+#    #+#             */
/*   Updated: 2019/11/02 11:28:49 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../incs/mod1.hpp"

void	Input::update(void)
{
	this->mouse_xrel = 0;
	this->mouse_yrel = 0;
	this->mouse_ywheel = 0;
	while (SDL_PollEvent(&this->event))
	{
		if (this->event.type == SDL_QUIT)
			this->quit = SDL_TRUE;
		else if (this->event.type == SDL_KEYDOWN)
		{
			this->keys[event.key.keysym.scancode] = SDL_TRUE;
			if (this->keys[SDL_SCANCODE_ESCAPE])
			{
				this->quit = SDL_TRUE;
				break ;
			}
		}
		else if (this->event.type == SDL_KEYUP)
			this->keys[event.key.keysym.scancode] = SDL_FALSE;
		else if (this->event.type == SDL_MOUSEBUTTONDOWN)
			this->mouse[event.button.button] = SDL_TRUE;
		else if (this->event.type == SDL_MOUSEBUTTONUP)
			this->mouse[event.button.button] = SDL_FALSE;
		else if (this->event.type == SDL_MOUSEMOTION)
		{
			this->mouse_x = event.motion.x;
			this->mouse_y = event.motion.y;
			this->mouse_xrel = event.motion.xrel;
			this->mouse_yrel = event.motion.yrel;
		}
		else if (this->event.type == SDL_MOUSEWHEEL)
			this->mouse_ywheel = event.wheel.y;
	}
}
