#include "../minishell.h"

void get_input(t_redir *redirs, t_shell *shell);
void read_heredoc_input(t_redir *redirs, int fd[2]);

void handle_heredoc(t_command *cmds, t_shell *shell)
{
	int fd[2];
	char *line;
	t_redir *redirs;

	while (cmds)
	{
		redirs = cmds->redirs;
		while (redirs)
		{
			if (redirs->type == HEREDOC)
			{
				printf("Handling heredoc for delimiter: [%s]\n", redirs->file); // TODO: remove before turn in
				if (pipe(fd) == -1)
					print_error(shell, "minishell: pipe");
				read_heredoc_input(redirs, fd);
				close(fd[1]);
				redirs->fd = fd[0];
			}
			redirs = redirs->next;
		}
		cmds = cmds->next;
	}
}

void read_heredoc_input(t_redir *redirs, int fd[2])
{
	char *line;

	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strncmp(line, redirs->file, ft_strlen(redirs->file)))
		{
			free(line);
			return;
		}
		write(fd[1], line, strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
}
