/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 14:02:31 by ebatchas          #+#    #+#             */
/*   Updated: 2019/11/02 14:17:28 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.hpp"

int				ft_strns(char const *s, char c)
{
	int		i;
	int		number;

	i = 0;
	number = 0;
	while (s[i + 1])
	{
		if (s[i] != c && s[i + 1] == c)
			number++;
		i++;
	}
	if (s[i] != c)
		number++;
	return (number);
}

static int		ft_check_init(char ***tab, char const **str, int *i, int *j)
{
	*i = 0;
	*j = 0;
	*tab = NULL;
	return ((*str) ? (1) : (0));
}

char			**ft_strsplit(char const *str, char c)
{
	char	**tab;
	int		i;
	int		j;
	int		k;

	if (ft_check_init(&tab, &str, &i, &k))
	{
		if ((tab = (char **)malloc(sizeof(char *) * (1 + ft_strns(str, c)))))
		{
			while (str[i] && k < ft_strns(str, c))
			{
				if ((tab[k] = (char *)malloc(255)))
				{
					j = 0;
					while (str[i] && str[i] != c)
						tab[k][j++] = str[i++];
					if (j)
						tab[k++][j] = '\0';
				}
				i++;
			}
			tab[k] = 0;
		}
	}
	return (tab);
}

void			ft_free_split(char ***tab)
{
	int		i;

	i = 0;
	while ((*tab)[i])
		free((*tab)[i++]);
	free(*tab);
	*tab = NULL;
}

int				ft_len_split(char **tab)
{
	int		i;

	i = -1;
	while (tab[++i])
		;
	return (i);
}
