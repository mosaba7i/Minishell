/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_copy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:37:18 by malsabah          #+#    #+#             */
/*   Updated: 2026/04/21 14:37:19 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	copy_before_split(char **new_lst, char **old_lst, int arg_index)
{
	int	i;

	i = 0;
	while (i < arg_index)
	{
		new_lst[i] = ft_strdup(old_lst[i]);
		i++;
	}
}

static void	copy_after_split(char **new_lst, char **old_lst, int old_i,
		int new_i)
{
	while (old_lst[old_i])
	{
		new_lst[new_i] = ft_strdup(old_lst[old_i]);
		old_i++;
		new_i++;
	}
	new_lst[new_i] = NULL;
}

static int	fill_split_args(char **new_lst, char *arg, int new_i)
{
	int	start;
	int	end;

	start = 0;
	while (arg[start])
	{
		while (arg[start] && is_white_space(arg[start]))
			start++;
		if (!arg[start])
			break ;
		end = find_split_pos(arg, start);
		new_lst[new_i] = ft_substr(arg, start, end - start);
		new_i++;
		start = end;
	}
	return (new_i);
}

void	split_var(char *arg, t_command *current_cmd, int arg_index,
		t_shell *shell)
{
	char	**new_arg_lst;
	int		old_count;
	int		split_count;
	int		new_i;

	split_count = count_splits(arg);
	if (split_count == 0)
		return ;
	old_count = count_arg_list(current_cmd->arg_lst);
	new_arg_lst = ft_calloc(old_count + split_count + 1, sizeof(char *));
	if (!new_arg_lst)
		print_error_free(shell, "minishell: malloc");
	copy_before_split(new_arg_lst, current_cmd->arg_lst, arg_index);
	new_i = arg_index;
	new_i = fill_split_args(new_arg_lst, arg, new_i);
	copy_after_split(new_arg_lst, current_cmd->arg_lst, arg_index + 1, new_i);
	free_args(current_cmd->arg_lst);
	current_cmd->arg_lst = new_arg_lst;
}
