/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_chars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:37:03 by malsabah          #+#    #+#             */
/*   Updated: 2026/04/21 14:37:04 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	substitute_expand_char(char *env_value)
{
	int	i;

	i = 0;
	while (env_value[i])
	{
		if (env_value[i] == '\'')
			env_value[i] = X_SQUOTE;
		else if (env_value[i] == '\"')
			env_value[i] = X_DQUOTE;
		else if (env_value[i] == '$')
			env_value[i] = X_DOLLAR;
		i++;
	}
}

char	get_expand_char(char c)
{
	if (c == '\'')
		return (X_SQUOTE);
	else if (c == '\"')
		return (X_DQUOTE);
	else if (c == '$')
		return (X_DOLLAR);
	return (c);
}
