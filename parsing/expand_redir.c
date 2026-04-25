/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:37:47 by malsabah          #+#    #+#             */
/*   Updated: 2026/04/21 14:37:48 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	search_var_redir(t_redir *redir, t_shell *shell)
{
	char	*pos;
	char	*var;

	if (redir->type == HEREDOC)
		return ;
	var = NULL;
	pos = ft_strchr(redir->file, '$');
	while (pos)
	{
		if (*(pos + 1) == '$')
		{
			pos = pos + 1;
			continue ;
		}
		get_var(pos, &var, shell);
		if (var && is_expandable(redir->file, var, &pos))
		{
			expand_var(var, &redir->file, shell, 1);
			pos = ft_strchr(redir->file, '$');
			continue ;
		}
		pos = ft_strchr(pos + 1, '$');
	}
}

int	multiple_redirs_same_file(t_redir *redir)
{
	int		i;
	char	*file;
	char	quote;

	if (redir->type == HEREDOC)
		return (0);
	i = 0;
	file = redir->file;
	quote = 0;
	while (file[i])
	{
		if (file[i] == '\'' || file[i] == '\"')
			quote = file[i];
		else if (quote && file[i] == quote)
			quote = 0;
		else if (!quote && is_white_space(file[i]))
			return (1);
		i++;
	}
	if (i == 0)
		return (1);
	return (0);
}
