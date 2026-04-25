/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:37:40 by malsabah          #+#    #+#             */
/*   Updated: 2026/04/21 14:37:41 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_pointers(const int pointer_count, ...)
{
	va_list	arguments;
	int		i;

	va_start(arguments, pointer_count);
	i = 0;
	while (i < pointer_count)
	{
		free(va_arg(arguments, void *));
		i++;
	}
	va_end(arguments);
}

void	expand_var(char *var, char **arg, t_shell *shell, int substitue)
{
	char	*env_value;
	char	*new_arg;
	int		new_len;

	env_value = get_expand_value(var, shell);
	new_len = get_new_arg_len(*arg, var, env_value);
	new_arg = ft_calloc(new_len + 1, sizeof(char));
	if (!new_arg)
	{
		free_pointers(2, var, env_value);
		print_error_free(shell, "minishell: malloc");
	}
	if (substitue)
		substitute_expand_char(env_value);
	replace_var(new_arg, env_value, *arg, var);
	free_pointers(3, *arg, var, env_value);
	*arg = new_arg;
}

char	*get_expand_value(char *var, t_shell *shell)
{
	char	*value;

	if (var[0] == '$' && !ft_isalpha(var[1]) && var[1] != '_')
		value = get_num(var, shell);
	else if (var[0] == '~')
		get_tilde_value(var, &value, shell);
	else
		value = get_env_expand_value(var, shell);
	if (!value)
	{
		free(var);
		print_error_free(shell, "minishell: malloc");
	}
	return (value);
}

void	search_tilde(t_command *cmds, t_shell *shell, int i)
{
	char	*var;

	if (cmds->arg_lst[i][0] != '~')
		return ;
	var = NULL;
	get_var(cmds->arg_lst[i], &var, shell);
	expand_var(var, &cmds->arg_lst[i], shell, 1);
}
