/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gettingpath.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 03:52:06 by malsabah          #+#    #+#             */
/*   Updated: 2026/02/25 03:52:09 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_envv(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(key) + 1) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

static int	has_slash(char *s)
{
	while (*s)
	{
		if (*s == '/')
			return (1);
		s++;
	}
	return (0);
}

static char	*mergepath(char *dir, char *cmd)
{
	char	*tmp;
	char	*out;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	out = ft_strjoin(tmp, cmd);
	free(tmp);
	return (out);
}

static char	*findpath(char *cmd, char **paths)
{
	int		i;
	char	*full;

	i = 0;
	while (paths && paths[i])
	{
		full = mergepath(paths[i], cmd);
		if (full && access(full, X_OK) == 0)
			return (full);
		free(full);
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(t_shell *shell, char *cmd)
{
	char	*path;
	char	**paths;
	char	*out;

	if (!cmd || !*cmd)
		return (NULL);
	if (has_slash(cmd))
		return (ft_strdup(cmd));
	path = get_envv(shell->env, "PATH");
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	out = findpath(cmd, paths);
	free_strs(paths);
	return (out);
}
