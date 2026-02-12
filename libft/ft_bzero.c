/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 02:18:12 by malsabah          #+#    #+#             */
/*   Updated: 2025/08/28 01:04:53 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

/*int main(void)
{
	int i = 0;

	char str[6] = "Hello";

	printf("Before: %s\n", str);

	ft_bzero(str, 5);

	while(i++ < 5 )
		printf("%d ", str[i]);

	printf("\nAfter: string is now empty\n");

	return (0);
}*/
