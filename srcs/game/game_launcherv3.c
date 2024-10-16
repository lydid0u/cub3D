/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_launcherv3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzinabi <adzinabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:13:22 by adzinabi          #+#    #+#             */
/*   Updated: 2024/10/09 15:17:12 by adzinabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	tourneragauche(t_info *info)
{
	info->olddirx = info->dirx;
	info->dirx = info->dirx * cos(info->rotspeed) - info->diry
		* sin(info->rotspeed);
	info->diry = info->olddirx * sin(info->rotspeed) + info->diry
		* cos(info->rotspeed);
	info->oldplanex = info->planex;
	info->planex = info->planex * cos(info->rotspeed) - info->planey
		* sin(info->rotspeed);
	info->planey = info->oldplanex * sin(info->rotspeed) + info->planey
		* cos(info->rotspeed);
}

void	tourneradroite(t_info *info)
{
	info->olddirx = info->dirx;
	info->dirx = info->dirx * cos(-info->rotspeed) - info->diry
		* sin(-info->rotspeed);
	info->diry = info->olddirx * sin(-info->rotspeed) + info->diry
		* cos(-info->rotspeed);
	info->oldplanex = info->planex;
	info->planex = info->planex * cos(-info->rotspeed) - info->planey
		* sin(-info->rotspeed);
	info->planey = info->oldplanex * sin(-info->rotspeed) + info->planey
		* cos(-info->rotspeed);
}

int	main_loop(t_info *info)
{
	if (info->touche.w == 1)
		avancer(info);
	if (info->touche.s == 1)
		reculer(info);
	if (info->touche.a == 1)
		agauche(info);
	if (info->touche.d == 1)
		adroite(info);
	if (info->touche.right == 1)
		tourneradroite(info);
	if (info->touche.left == 1)
		tourneragauche(info);
	if (info->touche.esc == 1)
		exit(1);
	calc(info);
	draw(info);
	return (0);
}

int	smallparsing(t_info *info)
{
	int	i;
	int	j;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
			info->buf[i][j++] = 0;
		i++;
	}
	info->texture = (int **)malloc(sizeof(int *) * 8);
	if (!(info->texture))
		return (-1);
	i = 0;
	while (i < 8)
	{
		info->texture[i] = (int *)malloc(sizeof(int) * (TEXHEIGHT * TEXWIDTH));
		if (!(info->texture[i]))
			return (-1);
		i++;
	}
	return (extrapars(info), 0);
}
