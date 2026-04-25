/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 18:36:48 by malsabah          #+#    #+#             */
/*   Updated: 2026/04/21 15:14:15 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_args(char **args, int *exit_code);

int	ft_exit(t_shell *shell, char **args)
{
	int	exit_code;

	if (shell->is_parent)
		printf("exit\n");
	exit_code = shell->exit_status;
	if (check_args(args, &exit_code))
		return (1);
	if (args)
		free_ptrs(shell->ptrs->tokens, shell->ptrs->commands);
	free_env(shell);
	rl_clear_history();
	exit(exit_code);
	return (0);
}

static int	check_args(char **args, int *exit_code)
{
	long	num;
	int		overflow;

	overflow = 0;
	if (args && args[1])
	{
		num = ft_atol(args[1], &overflow);
		if (!is_valid_num(args[1]) || ft_strlen(args[1]) == 0 || overflow)
		{
			ft_fprintf(2, "minishell: exit: %s: numeric argument required\n",
				args[1]);
			*exit_code = 2;
		}
		else if (args[2])
		{
			ft_fprintf(2, "minishell: exit: too many arguments\n");
			return (1);
		}
		else
			*exit_code = (unsigned int)num % 256;
	}
	return (0);
}

static void	handle_sign(const char **str, int *minus)
{
	if (**str == '-' || **str == '+')
	{
		*minus *= (44 - **str);
		(*str)++;
	}
}

static void	handle_digit(const char *str, int minus, long long *result,
		int *overflow)
{
	while (*str >= '0' && *str <= '9')
	{
		if (*result > LONG_MAX / 10 || - *result < LONG_MIN / 10)
			*overflow = 1;
		else if (*result == LONG_MAX / 10)
			if ((minus == -1 && (*str - 48) > 8) || (minus == 1 && (*str
						- 48) > 7))
				*overflow = 1;
		*result = *result * 10 + (*str - 48);
		str++;
	}
}

long long	ft_atol(const char *str, int *overflow)
{
	int			minus;
	long long	result;

	if (!str)
		return (0);
	minus = 1;
	result = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	handle_sign(&str, &minus);
	handle_digit(str, minus, &result, overflow);
	return (result * minus);
}

/* is_valid_num moved to builtins/is_valid.c */

// tetstingg
/*int main(int ac, char **av)
{
	t_shell *shell = malloc(sizeof(t_shell));
	shell->exit_status = 0;
	ft_exit(shell, av);
}*/
