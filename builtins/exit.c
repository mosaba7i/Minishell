/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalkhati <lalkhati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 18:36:48 by malsabah          #+#    #+#             */
/*   Updated: 2026/03/27 19:12:35 by lalkhati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static long long ft_atol(const char *str, int *overflow);
static int is_valid_num(char *str_num);
static int check_args(char **args, int *exit_code);

int ft_exit(t_shell *shell, char **args)
{
	int exit_code;

	printf("exit\n");
	exit_code = shell->exit_status;
	if (check_args(args, &exit_code))
		return (1);
	if (args)
		free_all(shell->ptrs->tokens, shell->ptrs->commands);
	free_env(shell);
	rl_clear_history();
	exit(exit_code);
	return (0);
}

static int check_args(char **args, int *exit_code)
{
	long num;
	int overflow;

	overflow = 0;
	if (args && args[1])
	{
		if (args[2])
		{
			printf("minishell: exit: too many arguments\n");
			return (1);
		}
		num = ft_atol(args[1], &overflow);
		if (!is_valid_num(args[1]) || ft_strlen(args[1]) == 0 || overflow)
		{
			ft_fprintf(2, "minishell: exit: %s: numeric argument required\n", args[1]);
			*exit_code = 2;
		}
		else
			*exit_code = (unsigned int)num % 256;
	}
	return (0);
}

static long long ft_atol(const char *str, int *overflow)
{
	int minus;
	long long result;

	minus = 1;
	result = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
	{
		minus *= -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		if (result > LONG_MAX / 10 || -result < LONG_MIN / 10)
			*overflow = 1;
		else if (result == LONG_MAX / 10)
			if ((minus == -1 && (*str - 48) > 8) || (minus == 1 && (*str - 48) > 7))
				*overflow = 1;
		result = result * 10 + (*str - 48);
		str++;
	}
	return (result * minus);
}

static int is_valid_num(char *str_num)
{
	int i;

	i = 0;
	if (str_num[0] == '-' || str_num[0] == '+')
		i++;
	if ((str_num[0] == '-' || str_num[0] == '+') && !str_num[1])
		return (0);
	while (str_num[i])
	{
		if (!ft_isdigit(str_num[i]))
			return (0);
		i++;
	}
	return (1);
}

// tetstingg
/*int main(int ac, char **av)
{
	t_shell *shell = malloc(sizeof(t_shell));
	shell->exit_status = 0;
	ft_exit(shell, av);
}*/
