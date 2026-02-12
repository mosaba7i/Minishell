/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 01:20:42 by malsabah          #+#    #+#             */
/*   Updated: 2025/08/30 07:26:32 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *d, const void *s, size_t blocks)
{
	size_t			i;
	unsigned char	*dest_char;
	unsigned char	*src_char;

	dest_char = (unsigned char *)d;
	src_char = (unsigned char *)s;
	if (dest_char < src_char || dest_char >= src_char + blocks)
		return (ft_memcpy(d, s, blocks));
	i = blocks;
	while (i > 0)
	{
		i--;
		dest_char[i] = src_char[i];
	}
	return (d);
}
/*int main(void)
{
	char str[] = "Hello Gumball";
	ft_memmove(str + 7, str, 5);
	printf("Result after ft_memmove: %s\n", str);

	char buffer[] = "1234567890";
	ft_memmove(buffer + 3, buffer, 5);
	printf("with overlap: %s\n", buffer);

	return (0);
}*/
