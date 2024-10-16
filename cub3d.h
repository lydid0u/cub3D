/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzinabi <adzinabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:13:35 by adzinabi          #+#    #+#             */
/*   Updated: 2024/10/09 15:21:03 by adzinabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./libft/libft.h"
# include "./mlx/mlx/mlx.h"
# include "./srcs/gnl/get_next_line.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_EXIT 17
# define TEXWIDTH 64
# define TEXHEIGHT 64
# define MAPWIDTH 24
# define MAPHEIGHT 24
# define WIDTH 640
# define HEIGHT 480

# define SPACE ' '
# define TAB '\t'
# define ALLSPACES " \t"

# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3
# define CEILING 4
# define FLOOR 5

typedef struct t_key
{
	int					w;
	int					a;
	int					s;
	int					d;
	int					left;
	int					right;
	int					esc;
	int					q;
}						t_key;

typedef struct s_img
{
	void	*img;
	int		*data;

	int		size_l;
	int		bpp;
	int		endian;
	int		img_width;
	int		img_height;
}			t_img;

typedef struct s_jeu
{
	char	**map;
	char	**value;
	char	**file_map;
	char	***directions;
	char	**floor_colors;
	char	**ceiling_colors;
	char	**map_spaced;
	int		pos_i;
	int		pos_j;
	char	start_position;
	int		nb_line_file;
	int		nb_line_map;
	int		ok[7];
	size_t	longest_line;
}			t_jeu;

typedef struct s_info
{
	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	double	planex;
	double	planey;
	void	*mlx;
	void	*win;
	t_img	img;
	int		buf[HEIGHT][WIDTH];
	int		**texture;
	double	movespeed;
	double	rotspeed;
	int		re_buf;
	double	camerax;
	double	raydirx;
	double	raydiry;
	double	deltadistx;
	double	deltadisty;
	int		stepx;
	int		stepy;
	double	sidedistx;
	double	sidedisty;
	int		mapx;
	int		mapy;
	int		side;
	int		lineheight;
	int		drawstart;
	int		drawend;
	double	perpwalldist;
	int		texnum;
	double	wallx;
	int		texx;
	double	step;
	double	texpos;
	int		debut;
	int		fin;
	int		texy;
	int		color;
	int		y;
	double	olddirx;
	double	oldplanex;
	void	*path_e;
	void	*path_w;
	void	*path_n;
	void	*path_s;

	char	**worldmap;
	char	player;
	t_jeu	*jeu;
	t_key	touche;
}			t_info;

# define W 119
# define A 97
# define S 115
# define D 100

# define LEFT 65361
# define RIGHT 65363
# define UP 65362
# define ESCAPE 65307
# define DOWN 65364

// utils.c
void		print_tab(char **tab);
void		free_tab(char **tab);
int			empty_line(char *str);

// parsing.c
int			filename(char *str);

int			key_release(int key, t_info *info);
// first_six_line.c
int			copy_map_value(char *file, t_jeu *jeu);
int			check_map_value(t_jeu *jeu);
int			check_direction(char *str, t_jeu *jeu);

// copy_map.c
int			copy_game_map(t_jeu *jeu);
void		count_line(char *file, t_jeu *jeu);

int			copy_file(char *file, t_jeu *jeu);
int			parsing_map(t_jeu *jeu);

int			error_handler(t_jeu *jeu);
void		free_tab_tab(char ***tab);

void		draw(t_info *info);
void		load_image(t_info *info, int *texture, char *path, t_img *img);
void		load_texture(t_info *info);
void		keypressingshortcut(t_info *info, int key);
int			key_press(int key, t_info *info);
void		extrapars(t_info *info);
int			smallparsing(t_info *info);
void		initbuffer(t_info *info);
void		calculateraydirection(t_info *info, int x);
void		calculatedeltadistances(t_info *info);
void		setstepandsidedist(t_info *info);
int			performdda(t_info *info);
double		calculateperpwalldist(t_info *info);
void		calculatelinedrawing(t_info *info);
double		calculatewallx(t_info *info);
int			calculatetexx(t_info *info);
void		fillbuffer(t_info *info, int x);
void		theend(t_info *info, int x);
void		calc(t_info *info);
int			main_loop(t_info *info);
void		keypressingfirstshortcut(t_info *info, int key);
void		singlehotkey(t_info *info, int key);
int			close_click(void *var);
void		free_texture(t_info *info);
void		destroy_win_disp(t_info *info);
void		direction_player_n_s(t_info *info, char direction);
void		direction_player_e_w(t_info *info, char direction);
void		wall_color(t_info *info);
void		fusion(t_jeu *jeu, t_info *info);
void		free_exit(t_jeu *jeu);
void		avancer(t_info *info);
void		reculer(t_info *info);
void		adroite(t_info *info);
void		agauche(t_info *info);

#endif