/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:41:07 by malsabah          #+#    #+#             */
/*   Updated: 2026/04/21 14:41:08 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_var(char *var_pos, char **var, t_shell *shell)
{
	int	i;

	if (var_pos[1] == '?' || ft_isdigit(var_pos[1]) || is_tilde(var_pos))
	{
		if (var_pos[1] == '\0' || var_pos[1] == '/' || var_pos[1] == ':')
			*var = ft_substr(var_pos, 0, 1);
		else
			*var = ft_substr(var_pos, 0, 2);
	}
	else
	{
		i = 1;
		while (var_pos[i])
		{
			if (var_pos[0] == '$' && !ft_isalnum(var_pos[i])
				&& var_pos[i] != '_')
				break ;
			i++;
		}
		*var = ft_substr(var_pos, 0, i);
	}
	if (!*var)
		print_error_free(shell, "minishell: malloc");
}

int	is_expandable(char *arg, char *var, char **var_pos)
{
	if (!ft_strcmp(var, "$") || inside_single_qoutes(arg, var_pos))
	{
		**var_pos = X_DOLLAR;
		free(var);
		return (0);
	}
	if (!ft_strncmp(arg, var, ft_strlen(arg)))
		return (1);
	if (!ft_strncmp(var, "~", 1) && inside_qoutes(arg, var_pos))
	{
		**var_pos = X_DOLLAR;
		free(var);
		return (0);
	}
	if (!ft_strncmp(var, "$?", 3))
		return (1);
	return (1);
}
