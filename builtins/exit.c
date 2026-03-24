/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalkhati <lalkhati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 18:36:48 by malsabah          #+#    #+#             */
/*   Updated: 2026/03/23 21:51:51 by lalkhati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_exit(t_shell *shell, char **args)
{
	int exit_code;

	printf("exit\n");
	exit_code = shell->exit_status;
	if (args[1])
	{
		if (args[2])
		{
			printf("minishell: exit: too many arguments\n");
			return (1);
		}
		exit_code = (unsigned int)ft_atoi(args[1]) % 256;
	}
	free_all(shell->ptrs->tokens, shell->ptrs->commands);
	free_env(shell);
	rl_clear_history();
	exit(exit_code);
	return (0);
}

// tetstingg
/*int main(int ac, char **av)
{
	t_shell *shell = malloc(sizeof(t_shell));
	shell->exit_status = 0;
	ft_exit(shell, av);
}*/