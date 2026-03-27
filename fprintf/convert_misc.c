/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_misc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalkhati <lalkhati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 14:36:25 by lalkhati          #+#    #+#             */
/*   Updated: 2025/09/18 14:51:56 by lalkhati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

char *char_to_string(char chara)
{
	char *new;

	new = malloc(2);
	if (!new)
		return (NULL);
	new[0] = chara;
	new[1] = '\0';
	return (new);
}

char *ft_address_char(void *addr)
{
	int i;
	char *hex_address;
	unsigned long long div;

	hex_address = (char *)malloc(18);
	div = (unsigned long long)addr;
	if (!addr)
	{
		ft_strcpy(hex_address, "(nil)");
		return (hex_address);
	}
	i = num_length(div, 16) + 1;
	hex_address[2 + num_length(div, 16)] = '\0';
	while (i >= 2)
	{
		hex_address[i] = "0123456789abcdef"[(div % 16)];
		div /= 16;
		i--;
	}
	hex_address[1] = 'x';
	hex_address[0] = '0';
	return (hex_address);
}

char *ft_strcpy(char *dest, char *src)
{
	int i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}