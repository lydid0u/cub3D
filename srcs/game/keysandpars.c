/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keysandpars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzinabi <adzinabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:34:16 by adzinabi          #+#    #+#             */
/*   Updated: 2024/10/10 15:48:28 by adzinabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	keypressingshortcut(t_info *info, int key)
{
	if (key == 65363)
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
	singlehotkey(info, key);
}

void	keypressingfirstshortcut(t_info *info, int key)
{
	if (key == 'd')
	{
		if (info->jeu->map_spaced[(int)(info->posx + (info->movespeed
					* cos(atan2(-info->dirx,
							info->diry))))][(int)(info->posy)] == '0')
			info->posx += info->movespeed * cos(atan2(-info->dirx, info->diry));
		if (info->jeu->map_spaced[(int)(info->posx)][(int)(info->posy
				+ (info->movespeed * sin(atan2(-info->dirx,
							info->diry))))] == '0')
			info->posy += info->movespeed * sin(atan2(-info->dirx, info->diry));
	}
	if (key == 'a')
	{
		if (info->jeu->map_spaced[(int)(info->posx - (info->movespeed
					* cos(atan2(-info->dirx,
							info->diry))))][(int)(info->posy)] == '0')
			info->posx -= info->movespeed * cos(atan2(-info->dirx, info->diry));
		if (info->jeu->map_spaced[(int)(info->posx)][(int)(info->posy
				- (info->movespeed * sin(atan2(-info->dirx,
							info->diry))))] == '0')
			info->posy -= info->movespeed * sin(atan2(-info->dirx, info->diry));
	}
}

int	key_release(int key, t_info *info)
{
	if (key == W)
		info->touche.w = 0;
	if (key == S)
		info->touche.s = 0;
	if (key == A)
		info->touche.a = 0;
	if (key == D)
		info->touche.d = 0;
	if (key == LEFT)
		info->touche.left = 0;
	if (key == RIGHT)
		info->touche.right = 0;
	if (key == ESCAPE || key == 'q')
		info->touche.esc = 0;
	return (0);
}

int	key_press(int key, t_info *info)
{
	if (key == W)
		info->touche.w = 1;
	if (key == S)
		info->touche.s = 1;
	if (key == A)
		info->touche.a = 1;
	if (key == D)
		info->touche.d = 1;
	if (key == LEFT)
		info->touche.left = 1;
	if (key == RIGHT)
		info->touche.right = 1;
	if (key == ESCAPE || key == 'q')
	{
		info->touche.esc = 1;
		mlx_destroy_image(info->mlx, info->img.img);
		destroy_win_disp(info);
		free_texture(info);
		free_exit(info->jeu);
		exit(1);
	}
	return (0);
}
	// if (key == 'w')
	// {
	// 	if (info->jeu->map_spaced[(int)(info->posx +
	//info->dirx * info->movespeed)][(int)(info->posy)] == '0')
	// 		info->posx += info->dirx * info->movespeed;
	// 	if (info->jeu->map_spaced[(int)(info->posx)][(int)(info->posy
	//+ info->diry * info->movespeed)] == '0')
	// 		info->posy += info->diry * info->movespeed;
	// }
	// if (key == 's')
	// {
	// 	if (info->jeu->map_spaced[(int)(info->posx - info->dirx
	//* info->movespeed)][(int)(info->posy)] == '0')
	// 		info->posx -= info->dirx * info->movespeed;
	// 	if (info->jeu->map_spaced[(int)(info->posx)][(int)(info->posy
	//- info->diry * info->movespeed)] == '0')
	// 		info->posy -= info->diry * info->movespeed;
	// }
	// keypressingfirstshortcut(info, key);
	// keypressingshortcut(info, key);
	// if (key == 'q' || key == 65307)
	// 	mlx_loop_end(info->mlx);
	// mlx_clear_window(info->mlx, info->win);
	// main_loop(info);

void	extrapars(t_info *info)
{
	int	i;
	int	j;

	i = 0;
	while (i < 8)
	{
		j = 0;
		while (j < TEXHEIGHT * TEXWIDTH)
		{
			info->texture[i][j] = 0;
			j++;
		}
		i++;
	}
}
