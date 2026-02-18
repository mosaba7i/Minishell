
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 18:53:00 by malsabah          #+#    #+#             */
/*   Updated: 2026/02/11 18:54:00 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_env(t_shell *shell)
{
    t_env *tmp;

    if (!shell || !shell->env)
        return (1);

    tmp = shell->env;
    while (tmp)
    {
        if (tmp->value)
            printf("%s=%s\n", tmp->key, tmp->value);
        tmp = tmp->next;
    }
    return (0);
}

// for testing only
/*int main(int ac,char **av,char **envp)
{
    //cc env.c ../init_shell.c export.c export_utils.c -L ../libft/ -lft
    t_shell *shell;

    shell = init_shell(envp);
    ft_env(shell);
    free_env(shell);
    return (0);
}*/
