/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:42:06 by malsabah          #+#    #+#             */
/*   Updated: 2026/04/21 15:04:08 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_quotes(char *arg)
{
	int		count;
	char	quote_type;

	count = 0;
	quote_type = 0;
	while (*arg)
	{
		if ((*arg == '\'' || *arg == '\"') && !quote_type)
			quote_type = *arg;
		else if (*arg == quote_type)
		{
			count++;
			quote_type = 0;
		}
		arg++;
	}
	return (count * 2);
}

void	get_quotes(char **arg, char **quote_pos)
{
	char	*start_quote;
	char	*end_quote;
	char	quote_type;
	int		i;

	i = -1;
	assign_null(2, &start_quote, &end_quote);
	while ((*arg)[++i])
	{
		if ((*arg)[i] == '\'' || (*arg)[i] == '\"')
		{
			quote_type = (*arg)[i];
			if (!start_quote)
				start_quote = &(*arg)[i];
			else if (!end_quote && quote_type == *start_quote)
				end_quote = &(*arg)[i];
			if (start_quote && end_quote)
			{
				quote_pos[0] = start_quote;
				quote_pos[1] = end_quote;
				quote_pos += 2;
				assign_null(2, &start_quote, &end_quote);
			}
		}
	}
}

char	*remove_quotes(char **arg, char **quote_pos, t_shell *shell)
{
	char	*new_arg;
	int		i;
	int		j;

	new_arg = ft_calloc(ft_strlen(*arg) - count_quotes(*arg) + 1, sizeof(char));
	if (!new_arg)
	{
		free(quote_pos);
		print_error_free(shell, "minishell: malloc");
	}
	i = 0;
	j = 0;
	while ((*arg)[i])
	{
		if (is_quote(&(*arg)[i], quote_pos))
		{
			i++;
			continue ;
		}
		new_arg[j++] = (*arg)[i++];
	}
	new_arg[j] = '\0';
	free(*arg);
	return (new_arg);
}

int	is_quote(char *pos, char **quote_pos)
{
	int	i;

	if (!quote_pos)
		return (0);
	i = 0;
	while (quote_pos[i])
	{
		if (pos == quote_pos[i])
			return (1);
		i++;
	}
	return (0);
}
