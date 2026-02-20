/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 11:55:20 by malsabah          #+#    #+#             */
/*   Updated: 2026/02/14 15:17:31 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <readline/readline.h> // readlinne (ext fun)
#include <readline/history.h>  // add_history, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay (ext func)
#include <stdio.h>			   // printf, perror, strerror
#include <stdlib.h>			   // malloc, free, exit, getenv
#include <unistd.h>			   // write, read, fork, execve, pipe, dup, dup2, chdir, getcwd, close
#include <fcntl.h>			   // open, O_RDONLY, O_WRONLY, O_CREAT, O_APPEND, O_TRUNC
#include <sys/wait.h>		   // wait, waitpid, wait3, wait4
#include <signal.h>			   // signal, sigaction, kill, sigemptyset, sigaddset
#include <dirent.h>			   // opendir, readdir, closedir
#include "./libft/libft.h"
#include <limits.h> // PATH_MAX
#include <errno.h>	// errno, perror, strerror
/*ext func like readline can be installed with
sudo apt-get update
sudo apt-get install libreadline-dev
*/

typedef struct s_redir
{
	char *file;
	int type;
	int fd;
	struct s_redir *next;
} t_redir;

typedef struct s_cmd
{
	int infile; // fd for infile
	int outfile;
	char **args;
	t_redir *redirs;
	int pipe[2];
	struct s_cmd *next;
} t_cmd;

// Lujain's structs for tokens and commands and redirections (feb 12)

typedef enum e_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_OUT_APP,
	HEREDOC
} t_type;

typedef struct s_token
{
	t_type type;
	char *value;
	struct s_token *next;
} t_token;

typedef struct s_commnad
{
	char **arg_lst;
	t_redir *redirs;
	struct s_commnad *next;
} t_commnad;

// typedef struct s_redir
// {
//     t_type type;
//     char   *file;
//     struct s_redir *next;
// } t_redir;

// new structs for env and shell (feb 14)
typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
} t_env;

typedef struct s_shell
{
	t_env *env; // linked list of environment variables
	int exit_status;
} t_shell;

// init and free funcs
t_shell *init_shell(char **envp);

// buitltin functions && thier helpers
void export_var(t_env **env, char *arg);
void get_key_value(char *arg, char **key, char **value);
void free_env(t_shell *shell);
void echo(char *s);
void pwd(void);
void export(t_shell *shell, char **args);
int ft_exit(t_shell *shell, char **args);
int ft_cd(t_shell *shell, t_cmd *cmd);
int ft_env(t_shell *shell);
int ft_unset(t_shell *shell, char **args);

// parsing functions
t_commnad *parse(t_token *tokens);
void handle_heredoc(t_commnad *cmds);
t_token *tokenize(char *input);

#endif
