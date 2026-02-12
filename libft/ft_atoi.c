/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 01:44:20 by malsabah          #+#    #+#             */
/*   Updated: 2025/08/27 23:02:36 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	s;
	int	i;
	int	r;

	s = 1;
	i = 0;
	r = 0;
	while ((str[i] == 32) || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		{
			s = s * -1;
		}
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = (r * 10) + (str[i] - '0');
		i++;
	}
	return (s * r);
}
/*int main()
{
   char arr[] = " ---+--+1234ab567";
   char arr1[] = " +1234ab567";
   char arr2[] = " -1234ab567";
	printf("%d", ft_atoi(arr));
	printf("%d", ft_atoi(arr1));
	printf("%d", ft_atoi(arr2));
	return (0);
}*/