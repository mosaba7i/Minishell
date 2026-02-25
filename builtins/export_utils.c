/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 15:11:00 by malsabah          #+#    #+#             */
/*   Updated: 2026/02/16 15:41:56 by malsabah         ###   ########.fr       */
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
        if (ft_strncmp(env->key, key, ft_strlen(key)) == 0)
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
int export_var(t_env **env, char *arg)
{
    char *equal;
    char *key;
    char *value;
    t_env *existing;

    if (!is_valid_identifier(arg))
    {
        printf("minishell: export: `%s': not a valid identifier\n", arg);
        return (1);
    }
    equal = ft_strchr(arg, '=');
    get_key_value(arg, &key, &value);
    existing = find_env(*env, key);
    if (existing && equal)
    {
        free(existing->value);
        existing->value = ft_strdup(value); // TODO: check malloc fail
    }
    else if (!existing)
        add_env_back(env, create_env_node(key, value));
    free(key);
    return (0);
}
