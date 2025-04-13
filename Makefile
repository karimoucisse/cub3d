NAME = cub3D
CC = cc
BONUS = bonus/
MANDATORY = mandatory/
PARSING = parsing/
RAYCASTING = raycasting/
CFLAGS = -Wall -Werror -Wextra -g
LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)libft.a

CFILES = $(MANDATORY)main.c $(MANDATORY)$(PARSING)check_file.c $(MANDATORY)$(PARSING)check_map.c $(MANDATORY)$(PARSING)check_texture.c\
    $(MANDATORY)player_move.c $(MANDATORY)utils.c $(MANDATORY)$(RAYCASTING)3draycasting.c $(MANDATORY)$(RAYCASTING)horizontal_intersection.c\
    $(MANDATORY)$(RAYCASTING)vertical_intersinction.c $(MANDATORY)$(RAYCASTING)check_direction.c $(MANDATORY)$(RAYCASTING)calculation.c\
    $(MANDATORY)init_structure.c $(MANDATORY)parsing.c $(MANDATORY)map_parsing.c $(MANDATORY)colors_fonctions.c $(MANDATORY)textures_fonctions.c
    
OFILES = $(CFILES:.c=.o)
CFILESBONUS = $(BONUS)main.c $(BONUS)$(PARSING)check_file.c $(BONUS)$(PARSING)check_map.c $(BONUS)$(PARSING)check_texture.c\
    $(BONUS)player_move.c $(BONUS)utils.c $(BONUS)$(RAYCASTING)3draycasting.c $(BONUS)$(RAYCASTING)check_intersections.c\
    $(BONUS)$(RAYCASTING)check_direction.c $(BONUS)$(RAYCASTING)calculation.c $(BONUS)$(RAYCASTING)minimap.c
OFILESBONUS = $(CFILESBONUS:.c=.o)
RM = rm -f

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) bonus

$(NAME): $(LIBFT) $(OFILES)
	$(CC) $(OFILES) -Lmlx -lmlx -L/usr/lib -Imlx -lXext -lX11 -lm -lz -L$(LIBFT_DIR) -lft -o $(NAME)

bonus: $(LIBFT) $(OFILESBONUS)
	$(CC) $(OFILESBONUS) -Lmlx -lmlx -L/usr/lib -Imlx -lXext -lX11 -lm -lz -L$(LIBFT_DIR) -lft -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -I ./includes -Imlx -O3 -c $< -o $@

clean:
	$(RM) $(OFILES) $(OFILESBONUS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus