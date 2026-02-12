/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 02:42:35 by malsabah          #+#    #+#             */
/*   Updated: 2025/08/28 22:46:18 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int chr)
{
	while (*str)
	{
		if (*str == (char)chr)
			return ((char *)str);
		str++;
	}
	if ((char)chr == '\0')
		return ((char *)str);
	return (NULL);
}
/*int main(void)
{
	char str[] = "Darwin and Gumball";
	char *result;

	result = ft_strchr(str, 'G');
	printf("Found 'G': %s\n", result);

	result = ft_strchr(str, 'b');
	printf("Found 'b: %s\n", result);

	return (0);
}*/