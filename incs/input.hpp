/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 18:30:36 by ebatchas          #+#    #+#             */
/*   Updated: 2019/11/12 18:55:53 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.hpp"

class	Input
{
	private:
		SDL_Event	event;

	public:
		SDL_bool	quit;
		SDL_bool	keys[SDL_NUM_SCANCODES];
		SDL_bool	mouse[6];
		int			mouse_x;
		int			mouse_y;
		int			mouse_xrel;
	   	int			mouse_yrel;
		int			mouse_ywheel;

		Input(){};
		void	update(void);
		~Input(){};
};
