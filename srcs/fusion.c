/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fusion.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:12:20 by lboudjel          #+#    #+#             */
/*   Updated: 2024/09/19 14:59:24 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fusion(t_jeu *jeu, t_info *info)
{
	info->posx = (double)(jeu->pos_i + 0.5);
	info->posy = (double)(jeu->pos_j + 0.5);
	info->path_e = jeu->directions[0][1];
	info->path_w = jeu->directions[1][1];
	info->path_s = jeu->directions[2][1];
	info->path_n = jeu->directions[3][1];
	info->worldmap = jeu->map_spaced;
	info->player = jeu->start_position;
	info->jeu = jeu;
}
