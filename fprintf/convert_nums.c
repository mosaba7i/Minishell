/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_nums.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalkhati <lalkhati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 14:36:25 by lalkhati          #+#    #+#             */
/*   Updated: 2025/09/18 14:51:45 by lalkhati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

int	num_length(long long num, long long base)
{
	unsigned long long	temp;
	int					length;

	temp = (unsigned long long)num;
	if (!temp)
		return (1);
	length = 0;
	while (temp)
	{
		length++;
		temp /= base;
	}
	return (length);
}

char	*num_to_string(char *char_base, long long num, int base)
{
	int		i;
	int		minus;
	char	*char_num;

	i = 0;
	minus = 0;
	if (num < 0)
	{
		num = -num;
		minus = 1;
		i = 1;
	}
	char_num = (char *)malloc(num_length(num, base) + 1 + minus);
	if (num == 0)
		char_num[i++] = '0';
	while (num > 0)
	{
		char_num[i] = char_base[(num % base)];
		num /= base;
		i++;
	}
	char_num[i] = '\0';
	if (minus)
		char_num[0] = '-';
	return (reverse_num(char_num, i - 1));
}

char	*num_to_string_unsighned(char *char_base, unsigned long long num,
		int base)
{
	int		i;
	char	*char_num;

	char_num = (char *)malloc(num_length(num, base) + 1);
	i = 0;
	if (num == 0)
		char_num[i++] = '0';
	while (num > 0)
	{
		char_num[i] = char_base[(num % base)];
		num /= base;
		i++;
	}
	char_num[i] = '\0';
	return (reverse_num(char_num, i - 1));
}

char	*reverse_num(char *num, int i)
{
	int		min;
	char	temp;

	min = 0;
	if (num[0] == '-')
		min = 1;
	while (i > min)
	{
		temp = num[min];
		num[min] = num[i];
		num[i] = temp;
		min++;
		i--;
	}
	return (num);
}
