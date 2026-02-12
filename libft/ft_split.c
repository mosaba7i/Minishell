/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 19:59:59 by malsabah          #+#    #+#             */
/*   Updated: 2025/08/29 15:25:49 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*word_dup(const char *start, const char *end)
{
	size_t	len;
	char	*out;
	size_t	i;

	len = (size_t)(end - start);
	out = (char *)malloc(len + 1);
	if (!out)
		return (NULL);
	i = 0;
	while (i < len)
	{
		out[i] = start[i];
		i++;
	}
	out[len] = '\0';
	return (out);
}

static size_t	count_words(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

static char	*next_word(const char **s, char c)
{
	const char	*start;
	const char	*end;
	char		*word;

	while (**s && **s == c)
		(*s)++;
	if (!**s)
		return (NULL);
	start = *s;
	while (**s && **s != c)
		(*s)++;
	end = *s;
	word = word_dup(start, end);
	return (word);
}

char	**ft_split(char const *s, char c)
{
	size_t	words;
	char	**array;
	size_t	i;

	words = count_words(s, c);
	array = (char **)malloc(sizeof(char *) * (words + 1));
	if (!array || !s)
		return (NULL);
	i = 0;
	while (i < words)
	{
		array[i] = next_word(&s, c);
		if (!array[i])
		{
			while (i--)
				free(array[i]);
			free(array);
			return (NULL);
		}
		i++;
	}
	array[i] = NULL;
	return (array);
}
/*int main(void) {
	char str[] = "   Hello  world 42   splits test   ";
	char **result;
	int i = 0;

	result = ft_split(str, ' ');

	while (result[i] != NULL) {
		printf("'%s'\n", result[i]);
		i++;
	}

	i = 0;
	while (result[i] != NULL) {
		free(result[i]);
		i++;
	}
	free(result);

	return (0);
}*/