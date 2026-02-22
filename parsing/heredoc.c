#include "../minishell.h"

void get_input(t_redir *redirs);

void handle_heredoc(t_commnad *cmds)
{
	while (cmds)
	{
		get_input(cmds->redirs);
		cmds = cmds->next;
	}
}

void get_input(t_redir *redirs)
{
	int fd[2];
	char *line;

	while (redirs)
	{
		if (redirs->type == HEREDOC)
		{
			if (pipe(fd) == -1)
				exit(1); // TODO: handle print error
			while (1)
			{
				line = readline("> ");
				if (!line || !ft_strncmp(line, redirs->file, ft_strlen(redirs->file)))
				{
					free(line);
					break;
				}
				write(fd[1], line, strlen(line));
				write(fd[1], "\n", 1);
				free(line);
			}
			close(fd[1]);
			redirs->fd = fd[0];
		}
		redirs = redirs->next;
	}
}
