/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:38:03 by malsabah          #+#    #+#             */
/*   Updated: 2026/04/21 14:38:04 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_arg_list(char **arg_lst)
{
	int	count;

	count = 0;
	while (arg_lst[count])
		count++;
	return (count);
}

void	free_args(char **arg_lst)
{
	int	i;

	i = 0;
	while (arg_lst[i])
	{
		free(arg_lst[i]);
		i++;
	}
	free(arg_lst);
}

int	count_splits(char *arg)
{
	int		i;
	int		split;
	char	inside_quote;

	i = 0;
	split = 0;
	inside_quote = 0;
	while (arg[i])
	{
		if (!inside_quote && (arg[i] == '\'' || arg[i] == '"'))
			inside_quote = arg[i];
		else if (inside_quote && arg[i] == inside_quote)
			inside_quote = 0;
		else if (is_white_space(arg[i]) && !inside_quote)
			split++;
		i++;
	}
	return (split);
}

int	find_split_pos(char *arg, int start)
{
	int		i;
	char	inside_quote;

	i = start;
	inside_quote = 0;
	while (arg[i])
	{
		if (!inside_quote && (arg[i] == '\'' || arg[i] == '"'))
			inside_quote = arg[i];
		else if (inside_quote && arg[i] == inside_quote)
			inside_quote = 0;
		else if (is_white_space(arg[i]) && !inside_quote)
			return (i);
		i++;
	}
	return (i);
}
