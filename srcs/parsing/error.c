/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:59:40 by lboudjel          #+#    #+#             */
/*   Updated: 2024/10/10 20:14:41 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_letters(t_jeu *jeu)
{
	int		i;
	int		j;
	char	**map;

	map = jeu->map_spaced;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!ft_strchr(" 10WNES", map[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

/*
int	check_wall(t_jeu *jeu)
{
	int		col;
	int		row;

	col = 0;
	while (jeu->map_spaced[col])
	{
		row = 0;
		while (jeu->map_spaced[col][row])
		{
			if (jeu->map_spaced[col][row] == ' ')
			{
				if (col != 0)
					if (!ft_strchr(" 1", jeu->map_spaced[col - 1][row]))
						return (printf("Error\n Missing a north wall\n"), 1);
				if (row != 0)
					if (!ft_strchr(" 1", jeu->map_spaced[col][row - 1]))
						return (printf("Error\n Missing a west wall\n"), 2);
				if (jeu->map_spaced[col + 1])
					if (!ft_strchr(" 1", jeu->map_spaced[col + 1][row]))
						return (printf("Error\n Missing a south wall\n"), 3);
				if (jeu->map_spaced[col][row + 1])
					if (!ft_strchr(" 1", jeu->map_spaced[col][row + 1]))
						return (printf("Error\n Missing a east wall\n"), 4);
			}
			row++;
		}
		col++;
	}
	return (0);
}
*/
int	check_wall(t_jeu *jeu)
{
	int (col) = 0;
	int (row);
	while (jeu->map_spaced[col])
	{
		row = 0;
		while (jeu->map_spaced[col][row])
		{
			if (jeu->map_spaced[col][row] == ' ')
			{
				if (col != 0 && !ft_strchr(" 1", jeu->map_spaced[col - 1][row]))
					return (printf("Error\n Missing a north wall\n"), 1);
				if (row != 0 && !ft_strchr(" 1", jeu->map_spaced[col][row - 1]))
					return (printf("Error\n Missing a west wall\n"), 2);
				if (jeu->map_spaced[col + 1])
					if (!ft_strchr(" 1", jeu->map_spaced[col + 1][row]))
						return (printf("Error\n Missing a south wall\n"), 3);
				if (jeu->map_spaced[col][row + 1])
					if (!ft_strchr(" 1", jeu->map_spaced[col][row + 1]))
						return (printf("Error\n Missing a east wall\n"), 4);
			}
			row++;
		}
		col++;
	}
	return (0);
}
// col + 1 cest pour si la ligne dapres nest pas null
// row + 1 cest pour si le char dapres nest pas null

int	check_position(t_jeu *jeu)
{
	int		i;
	int		j;
	int		letter;

	i = 0;
	letter = 0;
	while (jeu->map_spaced[i])
	{
		j = 0;
		while (jeu->map_spaced[i][j])
		{
			if (ft_strchr("WNES", jeu->map_spaced[i][j]))
			{
				jeu->start_position = jeu->map_spaced[i][j];
				jeu->map_spaced[i][j] = '0';
				jeu->pos_i = i + letter++;
				jeu->pos_j = j;
			}
			j++;
		}
		i++;
	}
	return (letter != 1);
}

int	error_handler(t_jeu *jeu)
{
	if (check_wall(jeu))
		return (1);
	if (check_letters(jeu))
		return (printf("Error\nA char is wrong !\n"), 1);
	if (check_position(jeu))
		return (printf("Error\nStart position !\n"), 1);
	return (0);
}
