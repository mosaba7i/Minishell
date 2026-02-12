/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 02:42:52 by malsabah          #+#    #+#             */
/*   Updated: 2025/08/28 22:43:33 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	while (s && *s)
	{
		write(fd, s, 1);
		s++;
	}
}
/*
int	main(void)
{
	  ft_putstr_fd("Hey there buddy \n", 1);
	  ft_putstr_fd("error\n", 2);
	return (0);
}
*/
