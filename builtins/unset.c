/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 15:10:57 by malsabah          #+#    #+#             */
/*   Updated: 2026/02/16 20:52:36 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_valid_identifier_unset(char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (0);
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	remove_env_key(t_env **env, char *key) // a -> b -> c  remove b , a->c
{
	t_env	*current;
	t_env	*previous;

	current = *env;
	previous = NULL;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0) //check if key matches
		{
			if (previous)
				previous->next = current->next;
			else
				*env = current->next;
			free_1env(current);
			return ;
		}
		previous = current;
		current = current->next;
	}
}

int	ft_unset(t_shell *shell, char **args)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	while (args[i])
	{
		if (!is_valid_identifier_unset(args[i]))
		{
			printf("minishell: unset: `%s': not a valid identifier\n", args[i]);
			status = 1;
		}
		else
			remove_env_key(&shell->env, args[i]);
		i++;
	}
	return (status);
    
}
