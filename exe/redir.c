/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 00:00:00 by malsabah          #+#    #+#             */
/*   Updated: 2026/04/20 14:05:22 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	dup_one_redir(int fd, t_redir *r)
{
	int	target;

	if (r->type == REDIR_IN || r->type == HEREDOC)
		target = STDIN_FILENO;
	else
		target = STDOUT_FILENO;
	if (dup2(fd, target) == -1)
	{
		perror("minishell: dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	do_redirs(t_redir *r)
{
	int	fd;

	while (r)
	{
		if (r->type == HEREDOC && r->fd == -1)
			return (-1);
		fd = open_one_redir(r);
		if (fd == -1)
			return (-1);
		if (dup_one_redir(fd, r) == -1)
			return (-1);
		r = r->next;
	}
	return (0);
}

int	apply_redirs(t_redir *r)
{
	return (do_redirs(r));
}
