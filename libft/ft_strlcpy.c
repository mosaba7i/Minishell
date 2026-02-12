/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 02:40:58 by malsabah          #+#    #+#             */
/*   Updated: 2025/08/28 16:31:01 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *source, size_t destsize)
{
	size_t	i;

	i = 0;
	if (destsize > 0)
	{
		while (source[i] != '\0' && i < destsize - 1)
		{
			dest[i] = source[i];
			i++;
		}
		if (destsize > 0)
			dest[i] = '\0';
	}
	while (source[i] != '\0')
		i++;
	return (i);
}
/*int main(void)
{
	char src[] = "EHHEHE";
	char dest[10];

	ft_strlcpy(dest, src, 10);
	printf("%s\n", dest);

	return (0);
}*/