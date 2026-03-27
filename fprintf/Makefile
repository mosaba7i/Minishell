NAME    = libftfprintf.a

LIBFT_DIRICTORY = ../libft
LIBFT_LIBRARY = $(LIBFT_DIRICTORY)/libft.a

CC      = cc
CFLAGS  = -Wall -Wextra -Werror
INCLUDES = -I$(LIBFT_DIRICTORY)
AR      = ar
ARFLAGS = rcs
RM      = rm -f

SRC     := ft_fprintf.c convert_nums.c parse_arguments.c convert_misc.c

OBJ     := $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(ARFLAGS) $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

