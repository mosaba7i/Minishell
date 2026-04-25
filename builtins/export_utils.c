/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:48:31 by malsabah          #+#    #+#             */
/*   Updated: 2026/04/21 14:48:32 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_valid_identifier(char *str)
{
	int	i;

	i = 0;
	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static t_env	*find_env(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
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

void	update_env(t_env **env, char *key, char **value, int *malloc_failed)
{
	t_env	*existing;
	int		equal;

	existing = find_env(*env, key);
	equal = (*value != NULL);
	if (existing && equal)
	{
		free(existing->value);
		if (*value)
		{
			existing->value = ft_strdup(*value);
			if (!existing->value)
			{
				free(key);
				*malloc_failed = 1;
				return ;
			}
		}
		else
			existing->value = NULL;
	}
	else if (!existing)
		add_env_back(env, create_env_node(key, *value));
	free(key);
}

int	export_var(t_env **env, char *arg)
{
	char	*equal;
	char	*key;
	char	*value;
	int		malloc_failed;

	malloc_failed = 0;
	if (!is_valid_identifier(arg))
	{
		ft_fprintf(2, "minishell: export: `%s': not a valid identifier\n", arg);
		return (1);
	}
	equal = ft_strchr(arg, '=');
	get_key_value(arg, &key, &value, &malloc_failed);
	if (malloc_failed)
		return (2);
	if (!value && equal)
		value = ft_strdup("");
	update_env(env, key, &value, &malloc_failed);
	if (malloc_failed)
		return (2);
	return (0);
}
