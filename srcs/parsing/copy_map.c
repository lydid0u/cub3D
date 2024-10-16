/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 18:53:45 by lboudjel          #+#    #+#             */
/*   Updated: 2024/10/10 19:50:57 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//compte le nombre de ligne de la map 
void	count_line(char *file, t_jeu *jeu)
{
	int		fd;
	char	*line;

	jeu->nb_line_file = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return ;
	line = get_next_line(fd, 0);
	while (line)
	{
		if (line == NULL)
			break ;
		jeu->nb_line_file++;
		free(line);
		line = get_next_line(fd, 0);
	}
	free(line);
	close(fd);
}

//jcopie le fichier grace a gnl
int	copy_file(char *file, t_jeu *jeu)
{
	char *(line);
	int (i) = 0;
	int (fd) = open(file, O_RDONLY);
	count_line(file, jeu);
	if (fd == -1 || read(fd, &line, 0) < 0)
		return (printf("Error\nThere is an error with the file !\n"), 1);
	jeu->file_map = malloc(sizeof(char *) * (jeu->nb_line_file + 1));
	if (!jeu->file_map)
		return (free(line), close(fd), 1);
	while (1)
	{
		line = get_next_line(fd, 0);
		if (line == NULL)
			break ;
		jeu->file_map[i] = malloc(ft_strlen(line) + 1);
		if (!jeu->file_map[i])
			return (free(line), close(fd), 1);
		if (i == jeu->nb_line_file - 1)
			ft_strcpy_n(jeu->file_map[i], line);
		else
			ft_strcpy(jeu->file_map[i], line);
		free(line);
		i++;
	}
	return (jeu->file_map[i] = NULL, close (fd), 0);
}

int	copy_game_map_norm(t_jeu *jeu, int i, int count, int j)
{
	while (jeu->file_map[i] && empty_line(jeu->file_map[i]))
		i++;
	jeu->map = ft_calloc(sizeof(char *), ((jeu->nb_line_file - count) + 1));
	while (jeu->file_map[i])
	{
		if (jeu->file_map[i])
		{
			if (ft_strlen(jeu->file_map[i]) > jeu->longest_line)
				jeu->longest_line = ft_strlen(jeu->file_map[i]);
			jeu->map[j++] = ft_strdup(jeu->file_map[i]);
			jeu->nb_line_map++;
		}
		i++;
	}
	return (0);
}

//jcopie la map du jeu
int	copy_game_map(t_jeu *jeu)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (jeu->file_map[i])
	{
		if (!ft_strncmp(jeu->file_map[i], jeu->value[5],
				ft_strlen(jeu->value[5])))
		{
			i++;
			count++;
			break ;
		}
		count++;
		i++;
	}
	copy_game_map_norm(jeu, i, count, j);
	return (0);
}
