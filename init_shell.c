/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:40:14 by malsabah          #+#    #+#             */
/*   Updated: 2026/02/16 17:00:48 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell *init_shell(char **envp)
{
    t_shell *shell = malloc(sizeof(t_shell));
    if (!shell)
        return NULL;

    shell->env = NULL;
    shell->exit_status = 0;

    int i = 0;
    while (envp[i])
    {
        export_var(&shell->env, envp[i]);
        i++;
    }
    return shell;
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
    free(shell);
}

void free_1env(t_env *env)
{
    free(env->key);
    free(env->value);
    free(env);
}
