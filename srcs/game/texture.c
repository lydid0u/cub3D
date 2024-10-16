/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:35:26 by adzinabi          #+#    #+#             */
/*   Updated: 2024/10/10 20:12:36 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw(t_info *info)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			info->img.data[y * WIDTH + x] = info->buf[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
}

void	load_image(t_info *info, int *texture, char *path, t_img *img)
{
	int	x;

	int (y) = 0;
	img->img = mlx_xpm_file_to_image(info->mlx, path,
			&img->img_width, &img->img_height);
	if (!img->img)
	{
		free_texture(info);
		destroy_win_disp(info);
		free_exit(info->jeu);
		exit(printf("Error\nTexture Error\n"));
	}
	img->data = (int *)mlx_get_data_addr(img->img,
			&img->bpp, &img->size_l, &img->endian);
	while (y < img->img_height)
	{
		x = 0;
		while (x < img->img_width)
		{
			texture[img->img_width * y + x] = img->data[img->img_width * y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(info->mlx, img->img);
}

void	load_texture(t_info *info)
{
	t_img	img;

	load_image(info, info->texture[3], info->path_w, &img);
	load_image(info, info->texture[2], info->path_e, &img);
	load_image(info, info->texture[1], info->path_n, &img);
	load_image(info, info->texture[0], info->path_s, &img);
}

// fleche gauche
void	singlehotkey(t_info *info, int key)
{
	if (key == 65361)
	{
		info->olddirx = info->dirx;
		info->dirx = info->dirx * cos(info->rotspeed)
			- info->diry * sin(info->rotspeed);
		info->diry = info->olddirx * sin(info->rotspeed)
			+ info->diry * cos(info->rotspeed);
		info->oldplanex = info->planex;
		info->planex = info->planex * cos(info->rotspeed)
			- info->planey * sin(info->rotspeed);
		info->planey = info->oldplanex * sin(info->rotspeed)
			+ info->planey * cos(info->rotspeed);
	}
}

int	close_click(void *var)
{
	t_info	*info;

	info = (t_info *)var;
	if (info->img.img)
		mlx_destroy_image(info->mlx, info->img.img);
	destroy_win_disp(info);
	free_texture(info);
	free_exit(info->jeu);
	exit(1);
}
