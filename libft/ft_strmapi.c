/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 19:33:34 by malsabah          #+#    #+#             */
/*   Updated: 2025/08/29 15:21:42 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int i, char c))
{
	char			*res;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	res = malloc(ft_strlen(s) + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (s[i])
	{
		res[i] = f(i, s[i]);
		i++;
	}
	res[i] = '\0';
	return (res);
}
/*static char ft_2upper(unsigned int i, char chr )
{
	if (chr >= 'a' && chr <= 'z')
		chr -= 32;
	return (chr);
}
int	main(void) {
	char *result = ft_strmapi("gumball", ft_2upper);
	printf("Address of ft_2lower: %p\n", ft_2upper);
	printf("%s\n", result);

	free(result);
	return (0);
}*/
