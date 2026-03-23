/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalkhati <lalkhati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 17:38:51 by malsabah          #+#    #+#             */
/*   Updated: 2026/03/19 17:31:02 by lalkhati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	return (0);
}

int exe_builtin(t_shell *shell, t_command *cmd)
{
	int ret;

	ret = 0;
	if (ft_strncmp(cmd->arg_lst[0], "echo", 5) == 0)
		ret = ft_echo(cmd->arg_lst);
	else if (ft_strncmp(cmd->arg_lst[0], "cd", 3) == 0)
		ret = ft_cd(shell, cmd);
	else if (ft_strncmp(cmd->arg_lst[0], "pwd", 4) == 0)
		ret = pwd();
	else if (ft_strncmp(cmd->arg_lst[0], "export", 7) == 0)
		ret = export(shell, cmd->arg_lst);
	else if (ft_strncmp(cmd->arg_lst[0], "unset", 6) == 0)
		ret = ft_unset(shell, cmd->arg_lst);
	else if (ft_strncmp(cmd->arg_lst[0], "env", 4) == 0)
		ret = ft_env(shell);
	else if (ft_strncmp(cmd->arg_lst[0], "exit", 5) == 0)
		ret = ft_exit(shell, cmd->arg_lst);
	return (ret);
}