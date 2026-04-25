/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:37:27 by malsabah          #+#    #+#             */
/*   Updated: 2026/04/21 14:37:28 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_env_expansion(t_command *cmds, t_shell *shell)
{
	int	i;

	while (cmds)
	{
		i = 0;
		check_export(cmds, shell);
		while (cmds->arg_lst[i])
		{
			search_var(cmds, shell, i);
			if (ft_strlen(cmds->arg_lst[i]) == 0)
			{
				shift_args(cmds->arg_lst, i);
				continue ;
			}
			split_var(cmds->arg_lst[i], cmds, i, shell);
			search_tilde(cmds, shell, i);
			i++;
		}
		if (expand_redir(cmds->redirs, shell) == -1)
			return (-1);
		cmds = cmds->next;
	}
	return (0);
}

int	expand_redir(t_redir *redirs, t_shell *shell)
{
	while (redirs)
	{
		search_var_redir(redirs, shell);
		if (multiple_redirs_same_file(redirs))
			return (print_error_syntax("ambiguous redirect", redirs->file,
					shell));
		redirs = redirs->next;
	}
	return (0);
}

void	shift_args(char **arg_lst, int index)
{
	int	i;

	free(arg_lst[index]);
	i = index;
	while (arg_lst[i])
	{
		arg_lst[i] = arg_lst[i + 1];
		i++;
	}
}

void	search_var(t_command *cmds, t_shell *shell, int i)
{
	char	*pos;
	char	*var;

	var = NULL;
	pos = ft_strchr(cmds->arg_lst[i], '$');
	while (pos)
	{
		if (*(pos + 1) == '$')
		{
			*pos = X_DOLLAR;
			pos = pos + 1;
			continue ;
		}
		get_var(pos, &var, shell);
		if (var && is_expandable(cmds->arg_lst[i], var, &pos))
		{
			expand_var(var, &cmds->arg_lst[i], shell, 1);
			pos = ft_strchr(cmds->arg_lst[i], '$');
			continue ;
		}
		pos = ft_strchr(pos + 1, '$');
	}
}
