/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisationbis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzinabi <adzinabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 17:47:11 by adzinabi          #+#    #+#             */
/*   Updated: 2024/10/09 15:21:46 by adzinabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

	// for (int i = 0; info->jeu->map_spaced[i]; i++)
	// {
	// 	/* code */
	// }
double	calculateperpwalldist(t_info *info)
{
	double	r;
	double	x;

	if (info->side == 0)
	{
		r = (info->mapx - info->posx + (1 - info->stepx) / 2) / info->raydirx;
		return (r);
	}
	else
	{
		x = (info->mapy - info->posy + (1 - info->stepy) / 2) / info->raydiry;
		return (x);
	}
}

void	calculatelinedrawing(t_info *info)
{
	info->lineheight = (int)(HEIGHT / info->perpwalldist);
	info->drawstart = -info->lineheight / 2 + HEIGHT / 2;
	if (info->drawstart < 0)
		info->drawstart = 0;
	info->drawend = info->lineheight / 2 + HEIGHT / 2;
	if (info->drawend >= HEIGHT)
		info->drawend = HEIGHT - 1;
}

double	calculatewallx(t_info *info)
{
	if (info->side == 0)
		return (info->posy + info->perpwalldist * info->raydiry);
	else
		return (info->posx + info->perpwalldist * info->raydirx);
}

int	calculatetexx(t_info *info)
{
	info->wallx -= floor(info->wallx);
	info->texx = (int)(info->wallx * (double)TEXWIDTH);
	if (info->side == 0 && info->raydirx > 0)
		info->texx = TEXWIDTH - info->texx - 1;
	else if (info->side == 1 && info->raydiry < 0)
		info->texx = TEXWIDTH - info->texx - 1;
	return (info->texx);
}

	// if (info->drawstart > WIDTH)
	// 	info->drawstart = WIDTH;
	// if (info->drawend > WIDTH)
	// 	info->drawstart = WIDTH;
void	fillbuffer(t_info *info, int x)
{
	info->step = 1.0 * TEXHEIGHT / info->lineheight;
	info->texpos = (info->drawstart - HEIGHT / 2 + info->lineheight / 2)
		* info->step;
	info->debut = 0;
	info->fin = info->drawend;
	while (info->debut < info->drawstart)
	{
		if (info->debut > HEIGHT || x > WIDTH)
			break ;
		info->buf[info->debut][x] = 0x72512a;
		info->debut++;
	}
	while (info->fin < HEIGHT)
	{
		info->buf[info->fin][x] = 0x2514bc;
		info->fin++;
	}
}
