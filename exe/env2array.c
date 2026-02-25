/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 03:52:32 by malsabah          #+#    #+#             */
/*   Updated: 2026/02/25 03:52:34 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	env_count(t_env *env)
{
	int	c;

	c = 0;
	while (env)
	{
		c++;
		env = env->next;
	}
	return (c);
}

static char	*merge_key_value(char *k, char *v)
{
	char	*tmp;
	char	*out;

	tmp = ft_strjoin(k, "=");
	if (!tmp)
		return (NULL);
	out = ft_strjoin(tmp, v);
	free(tmp);
	return (out);
}

char	**env_to_array(t_env *env)
{
	char	**arr;
	int		i;

	arr = ft_calloc(env_count(env) + 1, sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	while (env)
	{
		if (env->value)
			arr[i++] = merge_key_value(env->key, env->value);
		env = env->next;
	}
	arr[i] = NULL;
	return (arr);
}

void	free_strs(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}
