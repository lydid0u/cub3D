/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_launcherv2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzinabi <adzinabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:30:00 by adzinabi          #+#    #+#             */
/*   Updated: 2024/10/09 15:12:57 by adzinabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	wall_color(t_info *info)
{
	if (info->side == 1)
	{
		if (info->raydiry > 0)
			info->color = info->texture[0][64 * info->texy + info->texx];
		else
			info->color = info->texture[1][64 * info->texy + info->texx];
	}
	else
	{
		if (info->raydirx > 0)
			info->color = info->texture[3][64 * info->texy + info->texx];
		else
			info->color = info->texture[2][64 * info->texy + info->texx];
	}
}

void	direction_player_n_s(t_info *info, char direction)
{
	if (direction == 'N')
	{
		info->dirx = -1.0;
		info->diry = 0.0;
		info->planex = 0.0;
		info->planey = 0.66;
	}
	if (direction == 'S')
	{
		info->dirx = 1.0;
		info->diry = 0.0;
		info->planex = 0.0;
		info->planey = -0.66;
	}
	else if (direction == 'E' || direction == 'W')
		direction_player_e_w(info, direction);
}

void	direction_player_e_w(t_info *info, char direction)
{
	if (direction == 'E')
	{
		info->dirx = 0.0;
		info->diry = 1.0;
		info->planex = 0.66;
		info->planey = 0.00;
	}
	if (direction == 'W')
	{
		info->dirx = 0.0;
		info->diry = -1.0;
		info->planex = -0.66;
		info->planey = 0.00;
	}
}

void	initbuffer(t_info *info)
{
	int	i;
	int	j;

	if (info->re_buf == 1)
	{
		i = 0;
		while (i < HEIGHT)
		{
			j = 0;
			while (j < WIDTH)
			{
				info->buf[i][j] = 0;
				j++;
			}
			i++;
		}
	}
}
