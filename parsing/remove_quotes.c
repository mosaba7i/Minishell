/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes_core.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:41:59 by malsabah          #+#    #+#             */
/*   Updated: 2026/04/21 14:42:00 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	resubstitute_expand_char(char **arg)
{
	int	i;

	i = 0;
	while ((*arg)[i])
	{
		if ((*arg)[i] == X_SQUOTE)
			(*arg)[i] = '\'';
		else if ((*arg)[i] == X_DQUOTE)
			(*arg)[i] = '\"';
		else if ((*arg)[i] == X_DOLLAR)
			(*arg)[i] = '$';
		i++;
	}
}

void	search_remove_quotes(char **arg, t_shell *shell)
{
	char	*new_arg;
	char	**quote_pos;

	if (count_quotes(*arg) > 0)
	{
		quote_pos = ft_calloc((count_quotes(*arg) + 1), sizeof(char *));
		if (!quote_pos)
			print_error_free(shell, "minishell: malloc");
		get_quotes(arg, quote_pos);
		new_arg = remove_quotes(arg, quote_pos, shell);
		*arg = new_arg;
		free(quote_pos);
	}
}

void	handle_quotes(t_command *cmds, t_shell *shell)
{
	int		i;
	t_redir	*redir_temp;

	while (cmds)
	{
		i = 0;
		while (cmds->arg_lst[i])
		{
			search_remove_quotes(&cmds->arg_lst[i], shell);
			resubstitute_expand_char(&cmds->arg_lst[i]);
			i++;
		}
		redir_temp = cmds->redirs;
		while (redir_temp)
		{
			if (redir_temp->file)
			{
				search_remove_quotes(&redir_temp->file, shell);
				resubstitute_expand_char(&redir_temp->file);
			}
			redir_temp = redir_temp->next;
		}
		cmds = cmds->next;
	}
}
