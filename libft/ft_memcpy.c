/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 02:44:44 by malsabah          #+#    #+#             */
/*   Updated: 2025/08/30 07:15:22 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *d, const void *s, size_t blocks)
{
	size_t	i;

	i = 0;
	while (i < blocks)
	{
		((unsigned char *)d)[i] = ((unsigned char *)s)[i];
		i++;
	}
	return (d);
}

/*int main(void)
{
	char src[6] = "Hello";
	char dest[6];
	size_t i = 0;

	ft_memcpy(dest, src, 6);

	printf("Source: %s\n", src);
	printf("Dest  : %s\n", dest);

	return (0);
}*/