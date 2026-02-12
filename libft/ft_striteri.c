/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 19:59:17 by malsabah          #+#    #+#             */
/*   Updated: 2025/08/29 01:52:42 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
/*static void ft_2lower(unsigned int index, char *chr)
{
	if (*chr >= 'A' && *chr <= 'Z')
		*chr += 32;
}

int	main(void)
{
	char str[] = "GuMbAlL";

	ft_striteri(str, ft_2lower);
	printf("Lowercase: %s\n", str);
	printf("Address of ft_2lower: %p\n", (void*)ft_2lower);
	return (0);
}*/