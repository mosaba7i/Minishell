/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalkhati <lalkhati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 14:51:44 by malsabah          #+#    #+#             */
/*   Updated: 2026/03/29 16:35:04 by lalkhati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void get_key_value(char *arg, char **key, char **value)
{
	char *equal = ft_strchr(arg, '=');
	if (equal)
	{
		*key = ft_substr(arg, 0, equal - arg);
		if (!*key)
			return;
		*value = equal + 1;
	}
	else
	{
		*key = ft_strdup(arg);
		if (!*key)
			return;
		*value = NULL;
	}
}
static void print_export_sorted(t_env *env)
{
	t_env *tmp;
	t_env *min;
	char *last;

	last = "";
	while (1)
	{
		tmp = env;
		min = NULL;
		while (tmp)
		{
			if (ft_strncmp(tmp->key, last, ft_strlen(tmp->key) + 1) > 0)
				if (!min || ft_strncmp(tmp->key, min->key, ft_strlen(tmp->key) + 1) < 0)
					min = tmp;
			tmp = tmp->next;
		}
		if (!min)
			break;
		printf("declare -x %s", min->key);
		if (min->value)
			printf("=\"%s\"", min->value);
		printf("\n");
		last = min->key;
	}
}

int export(t_shell *shell, char **args)
{
	int i;
	int return_value;

	i = 1;
	if (!args[1])
	{
		print_export_sorted(shell->env);
		return (0);
	}
	return_value = 0;
	while (args[i])
	{
		return_value = export_var(&shell->env, args[i]);
		if (return_value == 2)
			print_error_free(shell, "minishell: malloc");
		i++;
	}
	return (return_value);
}

// for testing only
/*int main(int ac,char **av,char** envp)
{
	//cc export.c export_utils.c ../init_shell.c -L ../libft -lft
	t_shell *shelly;
	shelly = init_shell(envp);
	export(shelly,av);
}*/
