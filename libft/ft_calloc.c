/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 02:47:17 by malsabah          #+#    #+#             */
/*   Updated: 2025/08/30 07:22:53 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (!ptr)
		return (ft_strdup(""));
	ft_bzero(ptr, count * size);
	return (ptr);
}

/*int main(void)
{
	int *arr;
	size_t n = 5;
	size_t i = 0;

	arr = (int *)ft_calloc(n, sizeof(int));
	if (!arr)
	{
		printf("Allocation failed\n");
		return (1);
	}

	while (i < n)
	{
		printf("%d ", arr[i]);
		i++;
	}
	printf("\n");

	free(arr);
	return (0);
}*/