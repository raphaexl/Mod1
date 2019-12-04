/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 01:06:20 by ebatchas          #+#    #+#             */
/*   Updated: 2019/11/02 16:50:50 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/mod1.hpp"

Image::Image()
{
	this->data = NULL;
	this->file_name = std::string("");
	this->n_channels = 0;
	this->alignement = 0;
	this->internal_format = 0;
	this->format = 0;
	this->type = 0;
	this->pitch = 0;
	this->width = 0;
	this->height = 0;
}

Image::Image(std::string file_name)
{
	this->data = NULL;
	this->n_channels = 0;
	this->alignement = 0;
	this->internal_format = 0;
	this->format = 0;
	this->type = 0;
	this->pitch = 0;
	this->width = 0;
	this->height = 0;
	this->file_name = file_name;
}

void	Image::Load(void)
{
	SDL_Surface	*img{NULL};

	if (!(img = IMG_Load(file_name.c_str())))
	{
		std::cerr<<"Error IMG_Load() "<<IMG_GetError()<<std::endl;
		exit(EXIT_FAILURE);
	}
	this->n_channels = img->format->BytesPerPixel;
	if (this->n_channels == 4)
	{
		if (img->format->Rmask == 0x000000FF)
		{
			this->format = GL_RGBA;
			this->type = GL_UNSIGNED_INT_8_8_8_8_REV;
		}
		else
		{
			this->format = GL_BGRA;
			this->type = GL_UNSIGNED_INT_8_8_8_8;
		}
		this->internal_format = GL_RGBA8;
	}
	else if (this->n_channels == 3)
	{
		if (img->format->Rmask == 0x000000FF)
		{
			this->format = GL_RGB;
			this->type = GL_UNSIGNED_BYTE;
		}
		else
		{
			this->format = GL_BGR;
			this->type = GL_UNSIGNED_BYTE;
		}
		this->internal_format = GL_RGB8;
	}
	this->alignement = 8;
	while (img->pitch % alignement)
		alignement >>= 1;
	glPixelStorei(GL_UNPACK_ALIGNMENT, alignement);
	this->pitch = (img->w * this->n_channels + alignement - 1) / alignement * alignement;
	if (img->pitch - this->pitch >= this->alignement)
		glPixelStorei(GL_UNPACK_ROW_LENGTH, img->pitch / this->n_channels);
	else
		glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
	this->width = img->w;
	this->height = img->h;
	this->data = new Uint32[this->n_channels * this->width * this->height];
	memcpy(this->data, img->pixels, img->format->BytesPerPixel * img->w * img->h);
	SDL_FreeSurface(img);
}
