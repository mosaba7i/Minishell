/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 02:20:05 by malsabah          #+#    #+#             */
/*   Updated: 2025/08/30 07:27:24 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*p1;
	const unsigned char	*p2;

	p1 = s1;
	p2 = s2;
	while (n--)
	{
		if (*p1 != *p2)
			return (*p1 - *p2);
		p1++;
		p2++;
	}
	return (0);
}
/*int main(void)
{
	char str1[] = "Hello";
	char str2[] = "Hello";
	char str3[] = "Mohammed";

	printf("Compare str1 and str2: %d\n", ft_memcmp(str1, str2, 5));
	printf("Compare str1 and str3: %d\n", ft_memcmp(str1, str3, 5));

	return (0);
}*/
