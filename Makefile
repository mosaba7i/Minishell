NAME	= minishell

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

FPRINTF_DIR	= fprintf
FPRINTF		= $(FPRINTF_DIR)/libftfprintf.a

SRCS	= main.c init_shell.c \
	parsing/tokenise.c parsing/parse.c parsing/heredoc.c parsing/expand.c parsing/remove_quotes.c \
	builtins/echo.c builtins/cd.c builtins/pwd.c builtins/env.c \
	builtins/export.c builtins/export_utils.c builtins/unset.c builtins/exit.c \
	exe/exe_helpers.c exe/sigs.c exe/env2array.c exe/gettingpath.c exe/redir.c exe/exe.c

OBJS	= $(SRCS:.c=.o)

READLINE	= -lreadline -lncurses

all: $(LIBFT) $(FPRINTF) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(FPRINTF):
	$(MAKE) -C $(FPRINTF_DIR)

$(NAME): $(OBJS) minishell.h
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(FPRINTF) $(READLINE) -o $(NAME)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(FPRINTF_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(FPRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
