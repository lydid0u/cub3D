/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:58:22 by lboudjel          #+#    #+#             */
/*   Updated: 2024/09/02 16:08:34 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	filename(char *str)
{
	char	*cub;

	if (ft_strlen(str) > 4)
	{
		cub = ft_strnstr(str, ".cub", ft_strlen(str));
		if (cub && ft_strlen(cub) == 4)
			return (0);
	}
	return (printf("Error\nFilename's not valid !\n"), 1);
}

int	malloc_space_map(t_jeu *jeu)
{
	int	i;

	i = 0;
	jeu->map_spaced = malloc(sizeof(char *) * (jeu->nb_line_map + 3));
	if (!jeu->map_spaced)
		return (1);
	while (i < jeu->nb_line_map + 2)
	{
		jeu->map_spaced[i] = ft_calloc(sizeof(char), (jeu->longest_line + 4));
		if (!jeu->map_spaced[i])
			return (1);
		ft_memset(jeu->map_spaced[i], ' ', (jeu->longest_line + 2));
		i++;
	}
	jeu->map_spaced[i] = NULL;
	return (0);
}

int	parsing_map(t_jeu *jeu)
{
	int	i;

	i = 0;
	malloc_space_map(jeu);
	while (jeu->map[i])
	{
		ft_memcpy(&jeu->map_spaced[i + 1][1], jeu->map[i],
			ft_strlen(jeu->map[i]));
		i++;
	}
	return (0);
}
