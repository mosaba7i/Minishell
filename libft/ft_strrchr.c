/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 02:40:08 by malsabah          #+#    #+#             */
/*   Updated: 2025/08/28 16:31:54 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int chr)
{
	const char	*l;

	l = NULL;
	while (*str)
	{
		if (*str == (char)chr)
			l = str;
		str++;
	}
	if ((char)chr == '\0')
		return ((char *)str);
	return ((char *)l);
}
/*int main(void)
{
	char *result = ft_strrchr("EHHEHE", 'H');
	printf("%s\n", result);

	return (0);
}*/