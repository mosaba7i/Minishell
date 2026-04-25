/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 15:10:57 by malsabah          #+#    #+#             */
/*   Updated: 2026/04/20 15:04:51 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	remove_env_key(t_env **env, char *key)
{
	t_env	*current;
	t_env	*previous;

	current = *env;
	previous = NULL;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
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
		remove_env_key(&shell->env, args[i]);
		i++;
	}
	return (status);
}
