/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 15:14:56 by ebatchas          #+#    #+#             */
/*   Updated: 2019/11/14 14:24:07 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod1.hpp"

int		main(int argc, char *argv[])
{
	if (argc == 2)
	{
		Mwindow	win = Mwindow(argv[1]);
		win.process_input();
	}
	return (0);
}
