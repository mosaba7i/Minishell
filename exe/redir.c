/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 00:00:00 by malsabah          #+#    #+#             */
/*   Updated: 2026/02/26 04:43:51 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	open_inputfile(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		perror(file);
	return (fd);
}

static int	open_outputfile(char *file, int append)
{
	int	fd;

	if (append)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		perror(file);
	return (fd);
}

int	do_redirs(t_redir *r)
{
	int	fd;

	while (r)
	{
		if (r->type == HEREDOC && r->fd == -1)
			return (-1);
		if (r->type == REDIR_IN)
			fd = open_inputfile(r->file);
		else if (r->type == REDIR_OUT)
			fd = open_outputfile(r->file, 0);
		else if (r->type == REDIR_OUT_APP)
			fd = open_outputfile(r->file, 1);
		else
			fd = r->fd;
		if (fd == -1)
			return (-1);
		if (r->type == REDIR_IN || r->type == HEREDOC)
			dup2(fd, 0);
		else
			dup2(fd, 1);
		if (r->type != HEREDOC)
			close(fd);
		r = r->next;
	}
	return (0);
}
