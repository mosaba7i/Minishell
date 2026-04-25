/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_null.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:36:57 by malsabah          #+#    #+#             */
/*   Updated: 2026/04/21 14:36:58 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	assign_null(int num, ...)
{
	va_list	arguments;
	int		i;
	void	**current;

	va_start(arguments, num);
	i = 0;
	while (i < num)
	{
		current = va_arg(arguments, void **);
		*current = NULL;
		i++;
	}
	va_end(arguments);
}
