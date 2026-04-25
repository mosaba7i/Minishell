/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 02:34:20 by malsabah          #+#    #+#             */
/*   Updated: 2026/04/21 15:09:53 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	run_pipeline(t_shell *shell, t_command *cmd_list)
{
	int			last_input_fd;
	int			pipe_fds[2];
	pid_t		last_child;
	int			started_any_child;
	t_exec_ctx	ctx;

	last_input_fd = -1;
	last_child = -1;
	started_any_child = 0;
	ctx.last_input_fd = &last_input_fd;
	ctx.pipe_fds = pipe_fds;
	ctx.started_any_child = &started_any_child;
	ctx.last_child = &last_child;
	while (cmd_list)
	{
		if (run_one_cmd(shell, cmd_list, &ctx) != 0)
			return (1);
		cmd_list = cmd_list->next;
	}
	safe_close(&last_input_fd);
	return (wait_for_everything(last_child));
}
