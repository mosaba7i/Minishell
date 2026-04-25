/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_replace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:37:54 by malsabah          #+#    #+#             */
/*   Updated: 2026/04/21 14:37:55 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	replace_var(char *new_arg, char *env_value, char *arg, char *var)
{
	int		i;
	int		new_len;
	char	*var_pos;

	new_len = get_new_arg_len(arg, var, env_value);
	var_pos = ft_strnstr(arg, var, ft_strlen(arg));
	i = 0;
	while (i < new_len)
	{
		if (arg == var_pos)
		{
			if (env_value)
			{
				ft_strlcat(new_arg, env_value, new_len);
				i += ft_strlen(env_value) - 1;
			}
			else
				i--;
			arg += ft_strlen(var) - 1;
		}
		else
			new_arg[i] = *arg;
		arg++;
		i++;
	}
}

int	get_new_arg_len(char *arg, char *var, char *env_value)
{
	int	new_len;

	if (!env_value)
		new_len = ft_strlen(arg) - ft_strlen(var);
	else
		new_len = ft_strlen(arg) - ft_strlen(var) + ft_strlen(env_value);
	return (new_len + 1);
}
