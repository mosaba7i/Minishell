/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 17:38:51 by malsabah          #+#    #+#             */
/*   Updated: 2026/02/20 18:13:02 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(char *cmd)
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

int	exe_builtin(t_shell *shell, t_cmd *cmd)
{
	int	ret;

	ret = 0;
	if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		ret = ft_echo(cmd->args);
	else if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		ret = ft_cd(shell, cmd->args);
	else if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		ret = pwd();
	else if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		ret = export(shell, cmd->args);
	else if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		ret = ft_unset(shell, cmd->args);
	else if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		ret = ft_env(shell);
	else if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		ret = ft_exit(shell, cmd->args);
	return (ret);
}