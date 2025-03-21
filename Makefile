NAME = cub3D
CC = cc
SRC = src/
PARSING = $(SRC)parsing/
CFLAGS =
CFILES = $(SRC)main.c $(PARSING)check_file.c $(PARSING)check_map.c $(PARSING)check_texture.c
OFILES = $(CFILES:.c=.o)
RM = rm -f

all: $(NAME)
$(NAME): $(OFILES)
	$(CC) $(OFILES) -Lmlx -lmlx -L/usr/lib -Imlx -lXext -lX11 -lm -lz -L./includes -lft -o $(NAME)
%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -I ./includes -Imlx -O3 -c $< -o $@
clean:
	$(RM) $(OFILES)
fclean: clean
	$(RM) $(NAME)
re: fclean all
.PHONY: all clean fclean re
