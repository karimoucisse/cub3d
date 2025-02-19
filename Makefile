NAME = cub3D
CC = cc
CFLAGS = -Wall -Werror -Wextra
CFILES =
OFILES = $(CFILES:.c=.o)
RM = rm -f

all: $(NAME)
$(NAME): $(OFILES)
	$(CC) $(OFILES) -Lmlx -lmlx -L/usr/lib -Imlx -lXext -lX11 -lm -lz -o $(NAME)
%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -Imlx -O3 -c $< -o $@
clean:
	$(RM) $(OFILES)
fclean: clean
	$(RM) $(NAME)
re: fclean all
.PHONY: all clean fclean re
