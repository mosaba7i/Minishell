NAME	= minishell

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

FPRINTF_DIR	= fprintf
FPRINTF		= $(FPRINTF_DIR)/libftfprintf.a

SRCS	= main.c main_utils.c main_utils2.c init_shell.c \
	parsing/tokenize.c parsing/tokenize_words.c parsing/tokenize_types.c \
	parsing/parse.c parsing/parse_helpers.c parsing/parse_syntax.c \
	parsing/expand.c parsing/expand_redir.c parsing/expand_get_var.c parsing/expand_utils.c \
	parsing/expand_chars.c parsing/expand_handlers.c parsing/expand_var_value.c parsing/expand_replace.c \
	parsing/expand_split_1.c parsing/expand_split_2.c parsing/expand_check_export.c parsing/assign_null.c \
	parsing/heredoc.c parsing/heredoc_sup.c \
	parsing/remove_quotes.c parsing/remove_quotes_utils.c \
	builtins/echo.c builtins/cd.c builtins/pwd.c builtins/env.c \
	builtins/export.c builtins/export_utils.c builtins/unset.c builtins/exit.c \
	builtins/export_list.c builtins/env_helpers.c builtins/env_list.c builtins/is_valid.c \
	exe/exe_helpers.c exe/exe_utils.c exe/sigs_handlers.c exe/sigs_init.c exe/env2array.c exe/gettingpath.c exe/redir.c exe/redir_io.c exe/run_child.c exe/child_cleanup.c exe/execute_core.c exe/execute_loop.c exe/execute_one.c exe/execute_pipeline.c exe/builtin_parent.c exe/exe.c

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
