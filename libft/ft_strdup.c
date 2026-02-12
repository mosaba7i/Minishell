/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 02:42:21 by malsabah          #+#    #+#             */
/*   Updated: 2025/08/28 23:02:08 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	size_t	i;
	char	*clone;

	len = ft_strlen(s1);
	clone = (char *)malloc(len + 1);
	if (!clone)
		return (NULL);
	i = 0;
	while (i < len)
	{
		clone[i] = s1[i];
		i++;
	}
	clone[len] = '\0';
	return (clone);
}
/*
int	main(void)
{
	char	*original;
	char	*copy;

	original = "Gumball";
	copy = ft_strdup(original);
	if (copy)
	{
		printf("%s\n", copy);
		free(copy);
	}
	return (0);
}
*/