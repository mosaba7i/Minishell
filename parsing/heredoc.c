/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_core.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:41:14 by malsabah          #+#    #+#             */
/*   Updated: 2026/04/21 20:48:23 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	can_expand_heredoc(t_redir *heredoc_redirs)
{
	int		expand;
	char	*delimeter;
	int		i;

	expand = 1;
	delimeter = heredoc_redirs->file;
	i = 0;
	while (delimeter[i])
	{
		if (delimeter[i] == '\'' || delimeter[i] == '\"')
		{
			expand = 0;
			break ;
		}
		i++;
	}
	return (expand);
}

int	start_heredoc(t_redir *redirs, t_shell *shell, int expand)
{
	pid_t	pid;
	int		fd[2];
	int		status;

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

void	free_heredoc(t_shell *shell, char *line)
{
	free(line);
	free_ptrs(shell->ptrs->tokens, shell->ptrs->commands);
	free_env(shell);
	rl_clear_history();
}

int	handle_heredoc(t_command *cmds, t_shell *shell)
{
	t_redir	*redirs;
	int		return_vl;
	int		expand;

	while (cmds)
	{
		redirs = cmds->redirs;
		while (redirs)
		{
			if (redirs->type == HEREDOC)
			{
				expand = can_expand_heredoc(redirs);
				search_remove_quotes(&redirs->file, shell);
				printf("Handling heredoc for delimiter: [%s]\n", redirs->file);
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
