/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 02:41:25 by malsabah          #+#    #+#             */
/*   Updated: 2025/08/28 16:41:30 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dest_len;

	i = 0;
	while (dest[i] != '\0' && i < size)
		i++;
	dest_len = i;
	j = 0;
	while (src[j] != '\0' && i + 1 < size)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (dest_len < size)
		dest[i] = '\0';
	while (src[j] != '\0')
		j++;
	return (dest_len + j);
}

/*int	main(void)
{
	char arr1[] = "Hello";
	char arr2[] = "lo";
	int results = ft_strlcat(arr1,arr2,7);
	int i = 0;
	while (arr1[i] != '\0')
	{
	printf("%c", arr1[i]);
	i++;
	}
	printf("%d", results);

}	*/
