NAME = cub3D
CC = cc
SRC = src/
CFLAGS = 
CFILES = $(SRC)main.c
OFILES = $(CFILES:.c=.o)
RM = rm -f

all: $(NAME)
$(NAME): $(OFILES)
	$(CC) $(OFILES) -Lmlx -lmlx -L/usr/lib -Imlx -lXext -lX11 -lm -lz -L./includes -lft -o $(NAME)
%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -I ./includes  -Imlx -O3 -c $< -o $@
clean:
	$(RM) $(OFILES)
fclean: clean
	$(RM) $(NAME)
re: fclean all
.PHONY: all clean fclean re
