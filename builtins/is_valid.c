/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:49:14 by malsabah          #+#    #+#             */
/*   Updated: 2026/04/21 15:15:05 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_num(char *str_num)
{
	int	i;

	if (!str_num)
		return (0);
	i = 0;
	while (str_num[i] == ' ' || (str_num[i] >= 9 && str_num[i] <= 13))
		i++;
	if (str_num[i] == '-' || str_num[i] == '+')
		i++;
	if (!ft_isdigit(str_num[i]))
		return (0);
	while (ft_isdigit(str_num[i]))
		i++;
	while (str_num[i] == ' ' || (str_num[i] >= 9 && str_num[i] <= 13))
		i++;
	if (str_num[i] != '\0')
		return (0);
	return (1);
}
