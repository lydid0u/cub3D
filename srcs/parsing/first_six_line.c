/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_six_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 21:14:37 by lboudjel          #+#    #+#             */
/*   Updated: 2024/10/10 20:14:04 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define ERRORFILE "Error\nValue Error\n"

int	copy_map_value(char *file, t_jeu *jeu)
{
	char *(line);
	int (fd) = open(file, O_RDONLY);
	int (i) = 0;
	if (fd == -1 || read(fd, &line, 0) < 0)
		return (printf("Error\nThere is an error with the file !\n"), 0);
	jeu->value = ft_calloc(sizeof(*jeu->value), 7);
	if (!jeu->value)
		return (1);
	while (1)
	{
		line = get_next_line(fd, 0);
		if (line && !empty_line(line))
		{
			jeu->value[i] = malloc(ft_strlen(line) + 1);
			if (!jeu->value[i])
				return (1);
			ft_strcpy(jeu->value[i++], line);
		}
		free(line);
		if (i == 6 || line == NULL)
			break ;
	}
	if (i != 6)
		return (get_next_line(fd, 1), printf(ERRORFILE), close(fd), 1);
	return (get_next_line(fd, 1), close (fd), 0);
}

int	check_rgb_ceiling(t_jeu *jeu)
{
	int	i;
	int	nb;

	i = 0;
	if (!jeu->directions[4])
		return (1);
	jeu->ceiling_colors = ft_split(jeu->directions[4][1], ',');
	while (jeu->ceiling_colors[i])
		i++;
	if (i != 3)
		return (printf("Error\nWith the ceiling's rgb value !\n"), 1);
	i = 0;
	while (i != 3)
	{
		nb = ft_atoi(jeu->ceiling_colors[i]);
		if (nb < 0 || nb > 255)
			return (1);
		i++;
	}
	return (0);
}

int	check_rgb_floor(t_jeu *jeu)
{
	int	i;
	int	nb;

	i = 0;
	if (!jeu->directions[5])
		return (1);
	jeu->floor_colors = ft_split(jeu->directions[5][1], ',');
	while (jeu->floor_colors[i])
		i++;
	if (i != 3)
		return (printf("Error\nWith the floor's rgb value !\n"), 1);
	i = 0;
	while (i != 3)
	{
		nb = ft_atoi(jeu->floor_colors[i]);
		if (nb < 0 || nb >= 255)
			return (printf("Error\nWith the floor's rgb value !\n"), 1);
		i++;
	}
	return (0);
}

int	check_map_value(t_jeu *jeu)
{
	int	i;

	i = 0;
	jeu->directions = ft_calloc(sizeof(char **), 7);
	while (jeu->value[i])
	{
		if (check_direction(jeu->value[i], jeu))
			return (printf("Error\nValue Error !\n"), 1);
		i++;
	}
	i = 0;
	while (i < 6)
	{
		if (!jeu->directions[i])
			return (printf("Error\nMissing value !\n"), 1);
		if ((!jeu->directions[i][1]) || jeu->directions[i][2])
			return (printf("Error\nToo many instructions on the line !\n"), 1);
		i++;
	}
	if (check_rgb_ceiling(jeu) || check_rgb_floor(jeu))
		return (printf("Error\nValue RGB\n"));
	return (0);
}

int	check_direction(char *str, t_jeu *jeu)
{
	int			i;
	int			check;
	static char	*tab[7] = {"NO", "SO", "EA", "WE", "C", "F"};

	i = 0;
	check = 0;
	while (tab[i])
	{
		if (!ft_strncmp(str, tab[i], ft_strlen(tab[i]))
			&& ft_isspace(str[ft_strlen(tab[i])]) && jeu->ok[i] == 0)
		{
			jeu->directions[i] = ft_split(str, ' ');
			jeu->ok[i] = 1;
			check = 1;
		}
		i++;
	}
	if (check == 0)
		return (1);
	return (0);
}
