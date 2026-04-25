/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:48:41 by malsabah          #+#    #+#             */
/*   Updated: 2026/04/21 14:48:42 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_env	*find_env_node(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(key) + 1) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

static t_env	*create_env_node(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
	new->next = NULL;
	return (new);
}

void	set_env_value(t_shell *shell, char *key, char *value)
{
	t_env	*node;

	if (!key || !shell)
		return ;
	node = find_env_node(shell->env, key);
	if (node)
	{
		free(node->value);
		if (value)
			node->value = ft_strdup(value);
		else
			node->value = NULL;
		return ;
	}
	node = create_env_node(key, value);
	if (node)
	{
		node->next = shell->env;
		shell->env = node;
	}
}

char	*get_env_value(t_shell *shell, char *key)
{
	t_env	*tmp;

	tmp = shell->env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key) + 1) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
