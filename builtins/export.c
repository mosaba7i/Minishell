/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 14:51:44 by malsabah          #+#    #+#             */
/*   Updated: 2026/04/20 15:05:14 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_key_value(char *arg, char **key, char **value, int *malloc_failed)
{
	char	*equal;

	equal = ft_strchr(arg, '=');
	if (equal)
	{
		*key = ft_substr(arg, 0, equal - arg);
		if (!*key)
		{
			*malloc_failed = 1;
			return ;
		}
		*value = equal + 1;
	}
	else
	{
		*key = ft_strdup(arg);
		if (!*key)
		{
			*malloc_failed = 1;
			return ;
		}
		*value = NULL;
	}
}

int	export(t_shell *shell, char **args)
{
	int	i;
	int	return_value;
	int	error;

	i = 1;
	if (!args[1])
	{
		print_export_sorted(shell->env);
		return (0);
	}
	return_value = 0;
	error = 0;
	while (args[i])
	{
		return_value = export_var(&shell->env, args[i]);
		if (return_value == 1)
			error = 1;
		if (return_value == 2)
			print_error_free(shell, "minishell: malloc");
		i++;
	}
	return (error);
}

// for testing only
/*int main(int ac,char **av,char** envp)
{
	//cc export.c export_utils.c ../init_shell.c -L ../libft -lft
	t_shell *shelly;
	shelly = init_shell(envp);
	export(shelly,av);
}*/
