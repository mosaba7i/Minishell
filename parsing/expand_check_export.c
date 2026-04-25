/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_check_export.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:37:10 by malsabah          #+#    #+#             */
/*   Updated: 2026/04/21 14:37:11 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_quotes(char *new_arg, char *var_pos, char *arg)
{
	size_t	prefix_len;
	size_t	var_len;
	size_t	i;

	if (!var_pos)
		return ;
	prefix_len = var_pos - arg;
	ft_strlcpy(new_arg, arg, prefix_len + 1);
	i = 1;
	if (var_pos[i] == '?' || ft_isdigit(var_pos[i]))
		i++;
	else
	{
		while (var_pos[i] && (ft_isalnum(var_pos[i]) || var_pos[i] == '_'))
			i++;
	}
	var_len = i;
	new_arg[prefix_len] = '"';
	ft_strlcpy(new_arg + prefix_len + 1, var_pos, var_len + 1);
	new_arg[prefix_len + 1 + var_len] = '"';
	ft_strlcpy(new_arg + prefix_len + 1 + var_len + 1,
		var_pos + var_len, ft_strlen(var_pos + var_len) + 1);
}

void	check_export(t_command *cmds, t_shell *shell)
{
	char	*pos_eq;
	char	*new_arg;
	int		i;
	size_t	len;

	if (!cmds->arg_lst[0] || ft_strcmp(cmds->arg_lst[0], "export") != 0)
		return ;
	i = 0;
	while (cmds->arg_lst[++i])
	{
		pos_eq = ft_strchr(cmds->arg_lst[i], '=');
		if (!pos_eq || !*(pos_eq + 1))
			continue ;
		new_arg = ft_strchr(pos_eq + 1, '$');
		if (!new_arg || inside_qoutes(cmds->arg_lst[i], &new_arg))
			continue ;
		len = ft_strlen(cmds->arg_lst[i]);
		new_arg = malloc(len + 3);
		if (!new_arg)
			print_error_free(shell, "minishell: malloc");
		add_quotes(new_arg, ft_strchr(pos_eq + 1, '$'), cmds->arg_lst[i]);
		free(cmds->arg_lst[i]);
		cmds->arg_lst[i] = new_arg;
	}
}
