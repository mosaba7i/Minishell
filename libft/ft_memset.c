/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 02:53:11 by malsabah          #+#    #+#             */
/*   Updated: 2025/08/28 22:21:40 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t blocks)
{
	size_t			i;
	unsigned char	*c;

	c = ptr;
	i = 0;
	while (i < blocks)
	{
		c[i++] = (unsigned char)value;
	}
	return (ptr);
}

/*int main(void)
{
	char str[10] = "abcdefghi";
	size_t i = 0;

	printf("Before: ");
	while (i < 9)
	{
		printf("%c", str[i]);
		i++;
	}
	printf("\n");

	ft_memset(str, 'X', 5);

	i = 0;
	printf("After:  ");
	while (i < 9)
	{
		printf("%c", str[i]);
		i++;
	}
	printf("\n");

	return (0);
}*/
