/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalkhati <lalkhati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:40:14 by malsabah          #+#    #+#             */
/*   Updated: 2026/03/27 17:56:59 by lalkhati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_pointers(t_shell *shell);
char *get_lvl(t_shell *shell, char *env_var);

t_shell *init_shell(char **envp)
{
	t_shell *shell;
	char *lvl_str;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		print_error_free(NULL, "minishell: malloc");

	init_pointers(shell);
	lvl_str = NULL;
	int i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "SHLVL=", 6) == 0)
			lvl_str = get_lvl(shell, envp[i]);
		if (export_var(&shell->env, envp[i]) == 2)
			print_error_free(shell, "minishell: malloc");
		i++;
	}
	if (!lvl_str)
		lvl_str = ft_strdup("SHLVL=1");
	if (lvl_str)
		export_var(&shell->env, lvl_str);
	export_var(&shell->env, "SHELL=minishell");
	free(lvl_str);
	return (shell);
}

void init_pointers(t_shell *shell)
{
	shell->env = NULL;
	shell->exit_status = 0;
	shell->fd_to_close = -1;
	shell->ptrs = malloc(sizeof(t_ptrs)); // keep track of tokens and commands for easy freeing later
	if (!shell->ptrs)
		print_error_free(shell, "minishell: malloc");
	shell->ptrs->tokens = NULL;
	shell->ptrs->commands = NULL;
}

void free_env(t_shell *shell)
{
	t_env *tmp;
	while (shell->env)
	{
		tmp = shell->env;
		shell->env = shell->env->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
	free(shell->ptrs);
	free(shell);
}

void free_1env(t_env *env)
{
	free(env->key);
	free(env->value);
	free(env);
}

char *get_lvl(t_shell *shell, char *env_var)
{
	long long lvl_num;
	int overflow;
	char *lvl;
	char *str_num;

	overflow = 0;
	lvl_num = 0;
	lvl = ft_strchr(env_var, '=');
	if (!lvl || !(++lvl))
		lvl_num = 1;
	lvl_num = !is_valid_num(lvl);
	if (!lvl_num)
	{
		lvl_num = ft_atol(lvl, &overflow);
		if (overflow || lvl_num < 0 || ++lvl_num >= 1000)
			lvl_num = 1;
	}
	str_num = ft_itoa(lvl_num);
	if (!str_num)
		print_error_free(shell, "minishell: malloc");
	lvl = ft_strjoin("SHLVL=", str_num);
	free(str_num);
	if (!lvl)
		print_error_free(shell, "minishell: malloc");
	return (lvl);
}
