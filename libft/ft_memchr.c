/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 19:20:01 by malsabah          #+#    #+#             */
/*   Updated: 2025/08/30 07:28:00 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	while (n--)
	{
		if (*(unsigned char *)s == (unsigned char)c)
			return ((void *)s);
		s = (unsigned char *)s + 1;
	}
	return (NULL);
}
/*int main(void)
{
	char str[] = "Gumball";
	char *result = ft_memchr(str, 'a', 7);

	if (result) {
		printf("Found 'a' at: %s\n", result);
	} else {
		printf("'a' not found\n");
	}

	return (0);
}*/