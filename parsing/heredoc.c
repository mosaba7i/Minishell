#include "../minishell.h"

extern int g_sign;

void get_input(t_redir *redirs, t_shell *shell);
void read_heredoc_input(t_redir *redirs, int fd[2], int expand, t_shell *shell);
int start_heredoc(t_redir *redirs, t_shell *shell, int expand);
int can_expand_heredoc(t_redir *heredoc_redirs);
char *get_var_heredoc(char *var_pos, t_shell *shell, char **line, int fd[2]);
void expand_heredoc(char **line, t_shell *shell, int fd[2]);

int handle_heredoc(t_command *cmds, t_shell *shell)
{
	t_redir *redirs;
	int return_vl;
	int expand;

	while (cmds)
	{
		redirs = cmds->redirs;
		while (redirs)
		{
			if (redirs->type == HEREDOC)
			{
				expand = can_expand_heredoc(redirs);
				search_remove_quotes(&redirs->file, shell);
				printf("Handling heredoc for delimiter: [%s]\n", redirs->file); // TODO: remove before turn in
				return_vl = start_heredoc(redirs, shell, expand);
				if (return_vl)
					return (return_vl);
			}
			redirs = redirs->next;
		}
		cmds = cmds->next;
	}
	return (0);
}

int can_expand_heredoc(t_redir *heredoc_redirs)
{
	int expand;
	char *delimeter;
	int i;

	expand = 1;
	delimeter = heredoc_redirs->file;
	i = 0;
	while (delimeter[i])
	{
		if (delimeter[i] == '\'' || delimeter[i] == '\"')
		{
			expand = 0;
			break;
		}
		i++;
	}
	return (expand);
}

int start_heredoc(t_redir *redirs, t_shell *shell, int expand)
{
	pid_t pid;
	int fd[2];
	int status;

	if (pipe(fd) == -1)
		print_error_free(shell, "minishell: pipe");
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		read_heredoc_input(redirs, fd, expand, shell);
		close(fd[1]);
		exit(0);
	}
	else
	{
		close(fd[1]);
		waitpid(pid, &status, 0);
		initsig_prompt();
	}
	redirs->fd = fd[0];
	if (WEXITSTATUS(status) == 130)
		return (130);
	return (0);
}

void free_heredoc(t_shell *shell, char *line)
{
	free(line);
	free_ptrs(shell->ptrs->tokens, shell->ptrs->commands);
	free_env(shell);
	rl_clear_history();
}

void process_line(char *line, t_shell *shell, int expand, int fd[2])
{
	if (expand)
		expand_heredoc(&line, shell, fd);
	write(fd[1], line, strlen(line));
	write(fd[1], "\n", 1);
	free(line);
}

void read_heredoc_input(t_redir *redirs, int fd[2], int expand, t_shell *shell)
{
	char *line;

	initsig_heredoc();
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			if (g_sign == 2)
			{
				close(fd[1]);
				free_heredoc(shell, line);
				exit(130);
			}
			printf("minishell: warning: here-document delimited by end-of-file (wanted `%s')\n", redirs->file);
			free_heredoc(shell, line);
			return;
		}
		if (!ft_strcmp(line, redirs->file))
		{
			free_heredoc(shell, line);
			return;
		}
		process_line(line, shell, expand, fd);
	}
}

void expand_heredoc(char **line, t_shell *shell, int fd[2])
{
	char *pos;
	char *var;

	shell->fd_to_close = fd[1];
	pos = ft_strchr(*line, '$');
	while (pos)
	{
		if (*(pos + 1) == '$')
		{
			pos = pos + 1;
			continue;
		}
		var = get_var_heredoc(pos, shell, line, fd);
		if (var && ft_strcmp(var, "$") != 0)
		{
			expand_var(var, line, shell, 1);
			pos = ft_strchr(*line, '$');
			continue;
		}
		free(var);
		pos = ft_strchr(pos + 1, '$');
	}
}

char *get_var_heredoc(char *var_pos, t_shell *shell, char **line, int fd[2])
{
	int i;
	char *var;

	var = NULL;
	if (var_pos[1] == '?' || ft_isdigit(var_pos[1]))
		var = ft_substr(var_pos, 0, 2);
	else
	{
		i = 1;
		while (var_pos[i])
		{
			if (var_pos[0] == '$' && !ft_isalnum(var_pos[i]) && var_pos[i] != '_')
				break;
			i++;
		}
		var = ft_substr(var_pos, 0, i);
	}
	if (!var)
	{
		close(fd[1]);
		free(*line);
		print_error_free(shell, "minishell: malloc");
	}
	return (var);
}
