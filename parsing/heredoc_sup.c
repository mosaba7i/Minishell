/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_io.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:41:21 by malsabah          #+#    #+#             */
/*   Updated: 2026/04/21 20:48:11 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	process_line(char *line, t_shell *shell, int expand, int fd[2])
{
	if (expand)
		expand_heredoc(&line, shell, fd);
	write(fd[1], line, strlen(line));
	write(fd[1], "\n", 1);
	free(line);
}

static void	handle_heredoc_eof(t_redir *redirs, int fd[2], t_shell *shell,
		char *line)
{
	if (g_sign == 2)
	{
		close(fd[1]);
		free_heredoc(shell, line);
		exit(130);
	}
	printf("minishell: warning: here-document delimited by end-of-file ");
	printf("(wanted `%s')\n", redirs->file);
	free_heredoc(shell, line);
}

void	read_heredoc_input(t_redir *redirs, int fd[2], int expand,
		t_shell *shell)
{
	char	*line;

	initsig_heredoc();
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			handle_heredoc_eof(redirs, fd, shell, line);
			return ;
		}
		if (!ft_strcmp(line, redirs->file))
		{
			free_heredoc(shell, line);
			return ;
		}
		process_line(line, shell, expand, fd);
	}
}

void	expand_heredoc(char **line, t_shell *shell, int fd[2])
{
	char	*pos;
	char	*var;

	shell->fd_to_close = fd[1];
	pos = ft_strchr(*line, '$');
	while (pos)
	{
		if (*(pos + 1) == '$')
		{
			pos = pos + 1;
			continue ;
		}
		var = get_var_heredoc(pos, shell, line, fd);
		if (var && ft_strcmp(var, "$") != 0)
		{
			expand_var(var, line, shell, 1);
			pos = ft_strchr(*line, '$');
			continue ;
		}
		free(var);
		pos = ft_strchr(pos + 1, '$');
	}
}

char	*get_var_heredoc(char *var_pos, t_shell *shell, char **line, int fd[2])
{
	int		i;
	char	*var;

	var = NULL;
	if (var_pos[1] == '?' || ft_isdigit(var_pos[1]))
		var = ft_substr(var_pos, 0, 2);
	else
	{
		i = 1;
		while (var_pos[i])
		{
			if (var_pos[0] == '$' && !ft_isalnum(var_pos[i])
				&& var_pos[i] != '_')
				break ;
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
