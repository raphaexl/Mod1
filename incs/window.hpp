/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 15:21:03 by ebatchas          #+#    #+#             */
/*   Updated: 2019/11/14 17:43:20 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "sph.hpp"

class	Mwindow
{
	public:
		SDL_Window		*window;
		SDL_GLContext	context;
		Map				map;

		void	process_input(void);
		Mwindow(const char	*file_name);
		~Mwindow();
};
