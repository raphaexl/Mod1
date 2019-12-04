/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 12:44:20 by ebatchas          #+#    #+#             */
/*   Updated: 2019/11/02 14:25:36 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../incs/mod1.hpp"

Map::Map(){}
Map::~Map(){}

void	Map::Load(const char *file_name)
{
	std::ifstream	file;
	std::string 	read;

	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		std::stringstream sstr;

		file.open(file_name);
		sstr<<file.rdbuf();
		read = sstr.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cerr<<"Error loading you map file"<<std::endl;
		exit(EXIT_FAILURE);
	}
	const char	*str = read.c_str();

	if (str)
	{
		char		**split1 = NULL;
		char		**split2 = NULL;
		glm::vec3	vertex;

		if (!(split1 = ft_strsplit(str, '(')))
			exit(EXIT_FAILURE);
		int		i{-1};
		while (split1[++i])
		{
			if (!(split2 = ft_strsplit(split1[i], ',')) || ft_len_split(split2) != 3)
			{
				ft_free_split(&split1);
				exit(EXIT_FAILURE);
			}
			vertex.x = atof(split2[0]);
			vertex.y = atof(split2[1]);
			vertex.z = atof(split2[2]);
			this->data.push_back(vertex);
			ft_free_split(&split2);
			std::cout<<"vertex : "<<vertex.x<<" "<<vertex.y<<" "<<vertex.z<<std::endl;
		}
		ft_free_split(&split1);
	}
}
