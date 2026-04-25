/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigs_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 02:34:56 by malsabah          #+#    #+#             */
/*   Updated: 2026/04/21 20:47:53 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	hand_sigint(int sig)
{
	g_sign = sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	hand_sigint_heredoc(int sig)
{
	int	fd;

	fd = open("/dev/null", O_RDONLY);
	g_sign = sig;
	write(1, "\n", 1);
	dup2(fd, STDIN_FILENO);
	close(fd);
}
