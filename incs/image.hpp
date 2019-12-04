/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 00:56:23 by ebatchas          #+#    #+#             */
/*   Updated: 2019/11/02 13:09:20 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "camera.hpp"

class	Image
{
	public:
		std::string		file_name;
		GLenum			format;
		GLenum			internal_format;
		GLenum			type;
		GLuint			alignement;
		GLuint			n_channels;
		GLuint			pitch;
		GLuint			width;
		GLuint			height;
		Uint32			*data;
		Image();
		Image(std::string file_name);
		void	Load(void);
		~Image(){delete data;};
};
