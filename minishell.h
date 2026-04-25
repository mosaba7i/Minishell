/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 11:55:20 by malsabah          #+#    #+#             */
/*   Updated: 2026/04/21 21:36:44 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define TRUE 1
# define FALSE 0

# define X_SQUOTE '\x1D'
# define X_DQUOTE '\x1E'
# define X_DOLLAR '\x1F'

# include "./fprintf/ft_fprintf.h"
# include "./libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

extern int	g_sign;
typedef struct s_redir
{
	char				*file;
	int					type;
	int					fd;
	struct s_redir		*next;
}						t_redir;

typedef struct s_cmd
{
	int					infile;
	int					outfile;
	char				**args;
	t_redir				*redirs;
	int					pipe[2];
	struct s_cmd		*next;
}						t_cmd;

typedef enum e_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_OUT_APP,
	HEREDOC
}						t_type;

typedef struct s_token
{
	t_type				type;
	char				*value;
	struct s_token		*next;
}						t_token;

typedef struct s_command
{
	char				**arg_lst;
	t_redir				*redirs;
	struct s_command	*next;
}						t_command;

typedef struct s_ptrs
{
	t_token				*tokens;
	t_command			*commands;
}						t_ptrs;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_shell
{
	t_env				*env;
	t_ptrs				*ptrs;
	int					exit_status;
	int					fd_to_close;
	int					is_parent;
}						t_shell;

typedef struct s_exec_ctx
{
	int					*last_input_fd;
	int					*pipe_fds;
	int					*started_any_child;
	pid_t				*last_child;
}						t_exec_ctx;

typedef struct s_child_ctx
{
	int					input_fd;
	int					output_fd;
	char				*full_path;
	char				**env_list;
	t_shell				*shell;
}						t_child_ctx;

struct					s_quote_state
{
	char				inside_quote;
	char				*start_quote;
	char				*end_quote;
};

// init and free funcs
t_shell					*init_shell(char **envp);

// buitltin functions && thier helpers
int						export_var(t_env **env, char *arg);
void					get_key_value(char *arg, char **key, char **value,
							int *malloc_failed);
void					free_env(t_shell *shell);
void					free_1env(t_env *env);
int						ft_echo(char **args);
int						pwd(void);
int						export(t_shell *shell, char **args);
int						ft_exit(t_shell *shell, char **args);
int						ft_cd(t_shell *shell, t_command *cmd);
int						ft_env(t_shell *shell);
int						ft_unset(t_shell *shell, char **args);
int						ft_strcmp(const char *s1, const char *s2);

// execution functions
int						execute(t_shell *shell, t_command *command_list);
int						exe_builtin(t_shell *shell, t_command *cmd);
int						is_builtin(char *cmd);
char					**env_to_array(t_env *env);
void					free_strs(char **arr);
char					*get_cmd_path(t_shell *shell, char *cmd);
int						do_redirs(t_redir *r);
int						apply_redirs(t_redir *r);
// signals functions
void					initsig_child(void);
void					initsig_heredoc(void);
void					initsig_prompt(void);
void					initsig_parent(void);
// parsing functions
t_command				*parse(t_token *tokens, t_shell *shell);
int						handle_heredoc(t_command *cmds, t_shell *shell);
t_token					*tokenize(char *input, t_shell *shell);
int						is_white_space(char c);
void					assign_null(int num, ...);
int						check_env_expansion(t_command *cmds, t_shell *shell);
void					handle_quotes(t_command *cmds, t_shell *shell);
void					print_error_free(t_shell *shell, const char *msg);
int						print_error_syntax(char *msg, char *str,
							t_shell *shell);
void					free_tokens(t_token *head);
void					*free_ptrs(t_token *tokens, t_command *cmds);
void					reset_ptrs(t_shell *shell);
char					*get_env_value(t_shell *shell, char *key);
void					set_env_value(t_shell *shell, char *key, char *value);
int						is_path_directory(const char *path);
int						is_valid_num(char *str_num);
long long				ft_atol(const char *str, int *overflow);
void					search_remove_quotes(char **arg, t_shell *shell);
void					expand_var(char *var, char **arg, t_shell *shell,
							int substitute);
void					free_commands(t_command *head);
/* parse helpers */
int						count_args(t_token *tokens);
void					get_args(char **args, t_token *tokens, t_shell *shell);
t_redir					*get_redir(t_token *tokens, t_shell *shell);
void					append_redir(t_redir **head, t_redir *new);

/* split helpers */
int						count_splits(char *arg);
int						find_split_pos(char *arg, int start);

/* export helper */
void					check_export(t_command *cmds, t_shell *shell);

/* Additional parsing helper prototypes (refactored into parsing
	- multiple files) */
int						is_expandable(char *arg, char *var, char **var_pos);
int						inside_single_qoutes(char *arg, char **var_pos);
int						is_var_between(char **start_quote, char **end_quote,
							char **var_pos);
void					get_var(char *var_pos, char **var, t_shell *shell);
void					free_pointers(const int pointer_count, ...);
void					replace_var(char *new_arg, char *env_value, char *arg,
							char *var);
int						get_new_arg_len(char *arg, char *var, char *env_value);
void					search_var(t_command *cmds, t_shell *shell, int i);
int						inside_qoutes(char *arg, char **var_pos);
int						is_tilde(char *var);
void					get_tilde_value(char *var, char **env_value,
							t_shell *shell);
void					search_tilde(t_command *cmds, t_shell *shell, int i);
char					*get_num(char *var, t_shell *shell);
void					shift_args(char **arg_lst, int index);
char					*get_expand_value(char *var, t_shell *shell);
char					*get_env_expand_value(char *var, t_shell *shell);
void					substitute_expand_char(char *env_value);
int						count_arg_list(char **arg_lst);
void					free_args(char **arg_lst);
void					split_var(char *arg, t_command *current_cmd,
							int arg_index, t_shell *shell);
int						multiple_redirs_same_file(t_redir *redir);
void					search_var_redir(t_redir *redir, t_shell *shell);
int						expand_redir(t_redir *redirs, t_shell *shell);
int						check_syntax(t_token *tokens, t_shell *shell);
int						count_quotes(char *arg);
void					get_quotes(char **arg, char **quote_pos);
char					*remove_quotes(char **arg, char **quote_pos,
							t_shell *shell);
int						is_quote(char *pos, char **quote_pos);
int						is_var_between(char **start_quote, char **end_quote,
							char **var_pos);

/* syntax helpers */
int						is_redirection(char *str, int num);
int						is_operator_num(int num);

/* heredoc helpers */
void					expand_heredoc(char **line, t_shell *shell, int fd[2]);
char					*get_var_heredoc(char *var_pos, t_shell *shell,
							char **line, int fd[2]);
void					read_heredoc_input(t_redir *redirs, int fd[2],
							int expand, t_shell *shell);
int						can_expand_heredoc(t_redir *heredoc_redirs);
int						start_heredoc(t_redir *redirs, t_shell *shell,
							int expand);
void					free_heredoc(t_shell *shell, char *line);

/* tokenize helpers */
t_token					*new_token(void *content);
void					append_token(t_token **head, t_token *new);
void					assign_token_types(t_token *head);
int						extract_word(char *input, t_shell *shell, int i);
int						is_operator_char(char c);
int						get_operator(char *input, int word);

/* moved helpers */
void					print_export_sorted(t_env *env);
void					run_command_in_child(t_shell *shell, t_command *command,
							int input_fd, int output_fd);
void					print_cmd_not_found(char *cmd);
int						apply_and_exec_builtin(t_shell *shell,
							t_command *command);
void					safe_close(int *fd_to_close);
void					wait_for_leftovers(void);
int						wait_for_everything(pid_t last_child);
int						restore_stdio(int saved_stdin, int saved_stdout);
int						run_pipeline(t_shell *shell, t_command *cmd_list);
int						run_one_cmd(t_shell *shell, t_command *cmd,
							t_exec_ctx *ctx);
int						open_one_redir(t_redir *r);
void					add_env_back(t_env **env, t_env *new);

/* child cleanup helpers */
void					child_exit_cleanly(t_child_ctx *ctx, int exit_code);

#endif
