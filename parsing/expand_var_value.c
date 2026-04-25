/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:37:33 by malsabah          #+#    #+#             */
/*   Updated: 2026/04/21 14:37:34 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_expand_value(char *var, t_shell *shell)
{
	char	*value;
	char	*env_value;

	env_value = get_env_value(shell, var + 1);
	if (!env_value)
		return (ft_strdup(""));
	if (ft_strcmp(var, "$_") == 0 && ft_strrchr(env_value, '/')
		&& !is_path_directory(env_value))
		return (ft_strdup(ft_strrchr(env_value, '/') + 1));
	value = ft_strdup(env_value);
	return (value);
}

int	is_path_directory(const char *path)
{
	struct stat	stats;

	if (stat(path, &stats) == 0 && S_ISDIR(stats.st_mode))
		return (1);
	return (0);
}

char	*get_num(char *var, t_shell *shell)
{
	if (ft_strcmp(var, "$0") == 0)
		return (ft_strdup("minishell"));
	else if (var[0] == '$' && var[1] >= '1' && var[1] <= '9')
		return (ft_strdup(""));
	else if (var[1] == '?')
		return (ft_itoa(shell->exit_status));
	return (NULL);
}

void	get_tilde_value(char *var, char **env_value, t_shell *shell)
{
	char	*temp;

	if (var[1] == '\0' || var[1] == '/' || var[1] == ':')
		temp = get_env_value(shell, "HOME");
	else if ((var[1] == '+' || var[1] == '0') && (var[2] == '\0'
			|| var[2] == '/' || var[2] == ':'))
		temp = get_env_value(shell, "PWD");
	else if (var[1] == '-' && (var[2] == '\0' || var[2] == '/'
			|| var[2] == ':'))
		temp = get_env_value(shell, "OLDPWD");
	else if (ft_strcmp(var + 1, get_env_value(shell, "USER")) == 0)
		temp = get_env_value(shell, "HOME");
	else
		temp = var;
	if (!temp)
		temp = "";
	*env_value = ft_strdup(temp);
}
