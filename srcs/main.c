/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:55:29 by adzinabi          #+#    #+#             */
/*   Updated: 2024/10/10 20:02:20 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// retravailler ca
void	theend(t_info *info, int x)
{
	info->y = info->drawstart;
	while (info->y < info->drawend)
	{
		info->texy = (int)info->texpos & (TEXHEIGHT - 1);
		info->texpos += info->step;
		wall_color(info);
		if (info->side == 1)
			info->color = (info->color >> 1) & 8355711;
		info->buf[info->y][x] = info->color;
		info->re_buf = 1;
		info->y++;
	}
}

void	destroy_win_disp(t_info *info)
{
	if (info->win)
		mlx_destroy_window(info->mlx, info->win);
	if (info->mlx)
		mlx_destroy_display(info->mlx);
	free(info->mlx);
}

int	game(t_info *info)
{
	info->mlx = mlx_init();
	if (info->mlx == NULL)
		return (printf("Error\nmauvaise initialisation\n"), 0);
	info->re_buf = 0;
	direction_player_n_s(info, info->player);
	if (smallparsing(info) == -1)
		return (printf("Error\n parsing error\n"), free_texture(info), 0);
	load_texture(info);
	info->movespeed = 0.009;
	info->rotspeed = 0.007;
	info->win = mlx_new_window(info->mlx, WIDTH, HEIGHT, "mlx");
	if (info->win == NULL)
		return (printf("Error\nmauvaise initialisation\n"), 0);
	info->img.img = mlx_new_image(info->mlx, WIDTH, HEIGHT);
	info->img.data = (int *)mlx_get_data_addr(info->img.img, &info->img.bpp,
			&info->img.size_l, &info->img.endian);
	mlx_loop_hook(info->mlx, &main_loop, info);
	mlx_hook(info->win, 2, 1L << 0, &key_press, info);
	mlx_hook(info->win, 3, 1L << 1, &key_release, info);
	mlx_hook(info->win, 17, 0, &close_click, info);
	mlx_loop(info->mlx);
	mlx_destroy_image(info->mlx, info->img.img);
	destroy_win_disp(info);
	return (free_texture(info), 0);
}

int	parsing(char *file, t_jeu *jeu)
{
	if (filename(file))
		return (free_exit(jeu), 1);
	else if (copy_file(file, jeu))
		return (free_exit(jeu), 2);
	else if (copy_map_value(file, jeu))
		return (free_exit(jeu), 3);
	else if (check_map_value(jeu))
		return (free_exit(jeu), 4);
	else if (copy_game_map(jeu))
		return (free_exit(jeu), 5);
	else if (parsing_map(jeu))
		return (free_exit(jeu), 6);
	else if (error_handler(jeu))
		return (free_exit(jeu), 7);
	return (0);
}

int	main(int argc, char **argv)
{
	static t_jeu	jeu = {0};
	static t_info	info = {0};

	if (argc == 2)
	{
		if (parsing(argv[1], &jeu))
			return (1);
		fusion(&jeu, &info);
		if (game(&info) != 0)
			return (0);
		free_exit(&jeu);
	}
	else
		return (printf("Error\nArgs !\n"), 1);
	return (0);
}
//dans la fonction empty line rajouter tab aussi
