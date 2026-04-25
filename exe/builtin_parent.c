/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_parent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 02:32:44 by malsabah          #+#    #+#             */
/*   Updated: 2026/04/21 02:32:46 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	apply_and_exec_builtin(t_shell *shell, t_command *command)
{
	shell->is_parent = TRUE;
	if (apply_redirs(command->redirs) == -1)
		return (1);
	return (exe_builtin(shell, command));
}
