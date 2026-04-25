/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:48:36 by malsabah          #+#    #+#             */
/*   Updated: 2026/04/21 14:48:37 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_env	*find_min_key(t_env *env, char *last)
{
	t_env	*tmp;
	t_env	*min;

	tmp = env;
	min = NULL;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, last, ft_strlen(tmp->key) + 1) > 0)
			if (!min || ft_strncmp(tmp->key, min->key, ft_strlen(tmp->key)
					+ 1) < 0)
				min = tmp;
		tmp = tmp->next;
	}
	return (min);
}

static void	print_one_env(t_env *env)
{
	printf("declare -x %s", env->key);
	if (env->value)
		printf("=\"%s\"", env->value);
	printf("\n");
}

void	print_export_sorted(t_env *env)
{
	t_env	*min;
	char	*last;

	last = "";
	while (1)
	{
		min = find_min_key(env, last);
		if (!min)
			break ;
		print_one_env(min);
		last = min->key;
	}
}
