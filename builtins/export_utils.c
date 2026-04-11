/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalkhati <lalkhati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 15:11:00 by malsabah          #+#    #+#             */
/*   Updated: 2026/03/29 16:34:26 by lalkhati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int is_valid_identifier(char *str)
{
	int i = 0;

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

static t_env *find_env(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return env;
		env = env->next;
	}
	return NULL;
}

static t_env *create_env_node(char *key, char *value)
{
	t_env *new = malloc(sizeof(t_env));
	if (!new)
		return NULL;
	new->key = ft_strdup(key);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
	new->next = NULL;
	return new;
}

static void add_env_back(t_env **env, t_env *new)
{
	t_env *tmp;
	if (!*env)
	{
		*env = new;
		return;
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void update_env(t_env **env, char *key, char **value, char *equal)
{
	t_env *existing;

	existing = find_env(*env, key);
	if (existing && equal)
	{
		free(existing->value);
		existing->value = ft_strdup(*value); // TODO: check malloc fail
		if (!existing->value)
		{
			free(key);
			*value = NULL;
			return;
		}
	}
	else if (!existing)
		add_env_back(env, create_env_node(key, *value));
	free(key);
}

int export_var(t_env **env, char *arg)
{
	char *equal;
	char *key;
	char *value;

	if (!is_valid_identifier(arg))
	{
		ft_fprintf(2, "minishell: export: `%s': not a valid identifier\n", arg);
		return (1);
	}
	equal = ft_strchr(arg, '=');
	get_key_value(arg, &key, &value);
	if (!key)
		return (2);
	if (!value)
		value = "";
	update_env(env, key, &value, equal);
	if (!value)
		return (2);
	return (0);
}
