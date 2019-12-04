/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 12:54:22 by ebatchas          #+#    #+#             */
/*   Updated: 2019/11/12 18:56:17 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "defs.hpp"

class Map
{
	public:
		std::vector<glm::vec3>	data;;
		Map();
		void					Load(const char *file);
		~Map();
};

char			**ft_strsplit(char const *str, char c);
void			ft_free_split(char ***tab);
int				ft_len_split(char **tab);
