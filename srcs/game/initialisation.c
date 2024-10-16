/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzinabi <adzinabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 17:45:28 by adzinabi          #+#    #+#             */
/*   Updated: 2024/10/09 15:04:30 by adzinabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculateraydirection(t_info *info, int x)
{
	info->camerax = 2 * x / (double)WIDTH - 1;
	info->raydirx = info->dirx + info->planex * info->camerax;
	info->raydiry = info->diry + info->planey * info->camerax;
}

void	calculatedeltadistances(t_info *info)
{
	if (info->raydirx != 0)
		info->deltadistx = fabs(1 / info->raydirx);
	else
		info->deltadistx = 1e30;
	if (info->raydiry)
		info->deltadisty = fabs(1 / info->raydiry);
	else
		info->deltadisty = 1e30;
}

void	setstepandsidedist(t_info *info)
{
	if (info->raydirx < 0)
	{
		info->stepx = -1;
		info->sidedistx = (info->posx - info->mapx) * info->deltadistx;
	}
	else
	{
		info->stepx = 1;
		info->sidedistx = (info->mapx + 1.0 - info->posx) * info->deltadistx;
	}
	if (info->raydiry < 0)
	{
		info->stepy = -1;
		info->sidedisty = (info->posy - info->mapy) * info->deltadisty;
	}
	else
	{
		info->stepy = 1;
		info->sidedisty = (info->mapy + 1.0 - info->posy) * info->deltadisty;
	}
}

int	performdda(t_info *info)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (info->sidedistx < info->sidedisty)
		{
			info->sidedistx += info->deltadistx;
			info->mapx += info->stepx;
			info->side = 0;
		}
		else
		{
			info->sidedisty += info->deltadisty;
			info->mapy += info->stepy;
			info->side = 1;
		}
		if (info->worldmap[info->mapx][info->mapy] == '1')
			hit = 1;
	}
	return (hit);
}

void	free_texture(t_info *info)
{
	int	i;

	i = 0;
	if (info->texture)
	{
		while (i < 8)
		{
			free(info->texture[i]);
			i++;
		}
		free(info->texture);
		info->texture = NULL;
	}
}
