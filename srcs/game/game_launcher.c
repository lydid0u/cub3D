/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_launcher.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzinabi <adzinabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:05:28 by lboudjel          #+#    #+#             */
/*   Updated: 2024/10/09 15:13:39 by adzinabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc(t_info *info)
{
	int	x;
	int	hit;

	x = 0;
	initbuffer(info);
	while (x < WIDTH)
	{
		calculateraydirection(info, x);
		info->mapx = (int)info->posx;
		info->mapy = (int)info->posy;
		calculatedeltadistances(info);
		hit = 0;
		setstepandsidedist(info);
		hit = performdda(info);
		info->perpwalldist = calculateperpwalldist(info);
		calculatelinedrawing(info);
		info->texnum = info->worldmap[info->mapx][info->mapy] - '0';
		info->wallx = calculatewallx(info);
		info->texx = calculatetexx(info);
		fillbuffer(info, x);
		theend(info, x);
		x++;
	}
}

void	avancer(t_info *info)
{
	if (info->jeu->map_spaced[(int)(info->posx + info->dirx
			* info->movespeed)][(int)(info->posy)] == '0')
		info->posx += info->dirx * info->movespeed;
	if (info->jeu->map_spaced[(int)(info->posx)][(int)(info->posy + info->diry
			* info->movespeed)] == '0')
		info->posy += info->diry * info->movespeed;
}

void	reculer(t_info *info)
{
	if (info->jeu->map_spaced[(int)(info->posx - info->dirx
			* info->movespeed)][(int)(info->posy)] == '0')
		info->posx -= info->dirx * info->movespeed;
	if (info->jeu->map_spaced[(int)(info->posx)][(int)(info->posy - info->diry
			* info->movespeed)] == '0')
		info->posy -= info->diry * info->movespeed;
}

void	adroite(t_info *info)
{
	if (info->jeu->map_spaced[(int)(info->posx + (info->movespeed
				* cos(atan2(-info->dirx,
						info->diry))))][(int)(info->posy)] == '0')
		info->posx += info->movespeed * cos(atan2(-info->dirx, info->diry));
	if (info->jeu->map_spaced[(int)(info->posx)][(int)(info->posy
			+ (info->movespeed * sin(atan2(-info->dirx, info->diry))))] == '0')
		info->posy += info->movespeed * sin(atan2(-info->dirx, info->diry));
}

void	agauche(t_info *info)
{
	if (info->jeu->map_spaced[(int)(info->posx - (info->movespeed
				* cos(atan2(-info->dirx,
						info->diry))))][(int)(info->posy)] == '0')
		info->posx -= info->movespeed * cos(atan2(-info->dirx, info->diry));
	if (info->jeu->map_spaced[(int)(info->posx)][(int)(info->posy
			- (info->movespeed * sin(atan2(-info->dirx, info->diry))))] == '0')
		info->posy -= info->movespeed * sin(atan2(-info->dirx, info->diry));
}
