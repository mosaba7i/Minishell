#include "../minishell.h"

void get_input(t_redir *redirs, t_shell *shell);
void read_heredoc_input(t_redir *redirs, int fd[2]);
int start_heredoc(t_redir *redirs, t_shell *shell);

int handle_heredoc(t_command *cmds, t_shell *shell)
{
	t_redir *redirs;
	int return_vl;

	while (cmds)
	{
		redirs = cmds->redirs;
		while (redirs)
		{
			if (redirs->type == HEREDOC)
			{
				printf("Handling heredoc for delimiter: [%s]\n", redirs->file); // TODO: remove before turn in
				return_vl = start_heredoc(redirs, shell);
				if (return_vl)
					return (return_vl);
			}
			redirs = redirs->next;
		}
		cmds = cmds->next;
	}
	return (0);
}

int start_heredoc(t_redir *redirs, t_shell *shell)
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
		read_heredoc_input(redirs, fd);
		close(fd[1]);
		exit(0);
	}
	else
	{
		close(fd[1]);
		waitpid(pid, &status, 0);
		initsig_prompt();
		if (WEXITSTATUS(status) == 130)
			return (130);
	}
	redirs->fd = fd[0];
	return (0);
}

void read_heredoc_input(t_redir *redirs, int fd[2])
{
	char *line;

	initsig_heredoc();
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			printf("minishell: warning: here-document delimited by end-of-file (wanted `%s')\n", redirs->file);
			return;
		}
		if (!ft_strcmp(line, redirs->file))
		{
			free(line);
			return;
		}
		write(fd[1], line, strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
}
