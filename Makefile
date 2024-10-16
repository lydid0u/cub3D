NAME			=	cub3D

CC				=	cc

CFLAGS			=	-Wall -Wextra -Werror -g3 -Ofast -march=native # -Wall -Werror -Wextra

LIBFT          = libft
 
FT_LIBFT        = libft/libft.a

MLX				=	libmlx_Linux.a libmlx.a

DIR_SRCS		=	srcs

DIR_OBJS		=	objs

SRCS_NAMES		=	main.c game/keysandpars.c game/texture.c game/initialisation.c game/initialisationbis.c \
					game/game_launcher.c game/game_launcherv2.c game/game_launcherv3.c \
					parsing/parsing.c parsing/first_six_line.c parsing/utils.c parsing/copy_map.c \
					gnl/get_next_line.c gnl/get_next_line_utils.c \
					parsing/error.c fusion.c \

OBJS_NAMES		=	${SRCS_NAMES:.c=.o}

DEPS_NAMES		=	${SRCS_NAMES:.c=.d}

SRCS			=	$(addprefix $(DIR_SRCS)/,$(SRCS_NAMES))

OBJS			=	$(addprefix $(DIR_OBJS)/,$(OBJS_NAMES))

DEPS			=	$(addprefix $(DIR_OBJS)/,$(DEPS_NAMES))

INC				=	-Iincludes  -I/usr/include -I/mlx/include/mlx.h 

LIB				= -lm -lXext -lX11 -L/usr/lib -Lmlx -lXfixes -L/usr/lib -Imlx
 
#LIB				=	-Llibft -lm -L/usr/lib -L/opt/X11/lib -L/opt/homebrew/lib -framework Cocoa -framework OpenGL -framework IOKit -lglfw -framework OpenGL

CDFLAGS 		= 	-MMD -MP

HEAD	=	-I.

MAKEFLAGS		=	--no-print-directory

all:	${NAME}

# @make -C mlx/mlx
# mv mlx/mlx/libmlx.a mlx/mlx/libmlx_Linux.a mlx/
$(NAME): $(DIR_OBJS) $(OBJS) 
	@make -C $(LIBFT)
	@make -C mlx/mlx 
	@cp mlx/mlx/libmlx.a mlx/mlx/libmlx_Linux.a .
	$(CC) $(OBJS) $(CFLAGS) $(LIB) $(MLX) $(HEAD) -o $(NAME) $(FT_LIBFT)
	@echo "\033[32;5mcub3d\033[0m"

$(OBJS) : $(DIR_OBJS)/%.o : $(DIR_SRCS)/%.c
	$(CC) $(CFLAGS) $(MLX_FLAGS) $(CDFLAGS) $(INC) $(HEAD) -c $< -o $@ 

$(DIR_OBJS):
	mkdir -p $(DIR_OBJS)
	mkdir -p objs/parsing
	mkdir -p objs/game
	mkdir -p objs/gnl

leaks:	${NAME}
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./cub3D map.cub

clean:
	rm -rf ${DIR_OBJS}
	make clean -C mlx/mlx
	make clean -C libft

fclean:	clean
	make fclean -C libft
	rm -rf ${NAME}
	rm -rf ${MLX}
	rm -rf ${FT_LIBFT}

re:	fclean all

-include $(DEPS)

.PHONY:	all clean fclean re