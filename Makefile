NAME = cub3D
CC = cc
BONUS2 = bonus/
MANDATORY = mandatory/
PARSING = parsing/
RAYCASTING = raycasting/
CFLAGS = -Wall -Werror -Wextra -g
LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)libft.a

CFILES = $(MANDATORY)main.c\
    $(MANDATORY)player_move.c $(MANDATORY)utils.c $(MANDATORY)$(RAYCASTING)3draycasting.c $(MANDATORY)$(RAYCASTING)horizontal_intersection.c\
    $(MANDATORY)$(RAYCASTING)vertical_intersinction.c $(MANDATORY)$(RAYCASTING)check_direction.c $(MANDATORY)$(RAYCASTING)calculation.c\
    $(MANDATORY)init_structure.c $(MANDATORY)parsing.c $(MANDATORY)map_parsing.c $(MANDATORY)colors_fonctions.c $(MANDATORY)textures_fonctions.c\
	$(MANDATORY)key_action.c $(MANDATORY)map_parsing2.c $(MANDATORY)handle_end.c $(MANDATORY)init_structure2.c $(MANDATORY)put_pixels.c

OFILES = $(CFILES:.c=.o)
CFILESBONUS2 = $(BONUS2)main.c\
    $(BONUS2)player_move.c $(BONUS2)utils.c $(BONUS2)$(RAYCASTING)3draycasting.c $(BONUS2)$(RAYCASTING)horizontal_intersection.c\
    $(BONUS2)$(RAYCASTING)vertical_intersinction.c $(BONUS2)$(RAYCASTING)check_direction.c $(BONUS2)$(RAYCASTING)calculation.c\
	$(BONUS2)init_structure.c $(BONUS2)parsing.c $(BONUS2)map_parsing.c $(BONUS2)colors_fonctions.c\
	$(BONUS2)textures_fonctions.c $(BONUS2)key_action.c $(BONUS2)map_parsing2.c $(BONUS2)handle_end.c $(BONUS2)init_structure2.c\
	$(BONUS2)put_pixels.c $(BONUS2)minimap.c $(BONUS2)door_move.c

OFILESBONUS2 = $(CFILESBONUS2:.c=.o)
RM = rm -f

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) bonus

$(NAME): $(LIBFT) $(OFILES)
	$(CC) $(OFILES) -Lmlx -lmlx -L/usr/lib -Imlx -lXext -lX11 -lm -lz -L$(LIBFT_DIR) -lft -o $(NAME)

bonus: $(LIBFT) $(OFILESBONUS2)
	$(CC) $(OFILESBONUS2) -Lmlx -lmlx -L/usr/lib -Imlx -lXext -lX11 -lm -lz -L$(LIBFT_DIR) -lft -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -I ./includes -Imlx -O3 -c $< -o $@

clean:
	$(RM) $(OFILES) $(OFILESBONUS2)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re



# Makefile principal

# LIBFT_DIR = libft
# LIBFT_AR = libft.a
# LIB_DIR = lib

# all: $(LIB_DIR)/$(LIBFT_AR)
# 	# autres règles de compilation ici

# $(LIB_DIR)/$(LIBFT_AR):
# 	$(MAKE) -C $(LIBFT_DIR)
# 	mkdir -p $(LIB_DIR)
# 	cp $(LIBFT_DIR)/$(LIBFT_AR) $(LIB_DIR)/

# clean:
# 	$(MAKE) -C $(LIBFT_DIR) clean

# fclean:
# 	$(MAKE) -C $(LIBFT_DIR) fclean
# 	rm -f $(LIB_DIR)/$(LIBFT_AR)

# re: fclean all
