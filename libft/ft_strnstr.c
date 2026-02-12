/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 02:40:19 by malsabah          #+#    #+#             */
/*   Updated: 2025/08/30 05:39:55 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hay, const char *needle, size_t n)
{
	size_t	i;
	size_t	j;

	if (*needle == '\0')
		return ((char *)hay);
	i = 0;
	while (hay[i] != '\0' && i < n)
	{
		j = 0;
		while (hay[i + j] == needle[j] && i + j < n)
		{
			if (needle[j + 1] == '\0')
				return ((char *)&hay[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}

/*int main(void)
{
	printf("%s\n", ft_strnstr("new world", "world", 9));
	printf("%s\n", ft_strnstr("new world", "lo", 5));
	printf("%s\n", ft_strnstr("new world", "", 5));
}*/