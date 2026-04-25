/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 02:34:31 by malsabah          #+#    #+#             */
/*   Updated: 2026/04/21 15:10:51 by malsabah         ###   ########.fr       */
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

int	open_one_redir(t_redir *r)
{
	if (r->type == REDIR_IN)
		return (open_inputfile(r->file));
	if (r->type == REDIR_OUT)
		return (open_outputfile(r->file, 0));
	if (r->type == REDIR_OUT_APP)
		return (open_outputfile(r->file, 1));
	return (r->fd);
}
