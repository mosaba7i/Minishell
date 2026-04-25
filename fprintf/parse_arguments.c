/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalkhati <lalkhati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 14:36:25 by lalkhati          #+#    #+#             */
/*   Updated: 2025/09/18 14:51:36 by lalkhati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

int	parse_arguments(const char *text, char **full_text, va_list arguments,
		int arg_count)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (j < arg_count && text[i])
	{
		if (text[i] == '%')
		{
			full_text[j] = parse_specifier(text[i + 1], arguments);
			if (full_text[j] == NULL)
				return (0);
			else
				j++;
			i++;
		}
		i++;
	}
	return (1);
}

char	*parse_specifier(char specifier, va_list arguments)
{
	if (specifier == 'c')
		return (char_to_string(va_arg(arguments, int)));
	if (specifier == 'd' || specifier == 'i')
		return (num_to_string("0123456789", va_arg(arguments, int), 10));
	if (specifier == 's')
		return (ft_strdup_null(va_arg(arguments, char *)));
	if (specifier == 'p')
		return (ft_address_char(va_arg(arguments, void *)));
	if (specifier == 'u')
		return (num_to_string_unsighned("0123456789", va_arg(arguments,
					unsigned int), 10));
	if (specifier == 'x')
		return (num_to_string_unsighned("0123456789abcdef", va_arg(arguments,
					unsigned int), 16));
	if (specifier == 'X')
		return (num_to_string_unsighned("0123456789ABCDEF", va_arg(arguments,
					unsigned int), 16));
	if (specifier == '%')
		return (ft_strdup("%"));
	return (NULL);
}

int	process_output(const char *text, char **full_text, int arg_count, int fd)
{
	int		j;
	char	*percent_pos;
	int		length;

	length = 0;
	j = 0;
	while (j < arg_count && *text)
	{
		percent_pos = ft_strchr(text, '%');
		write(fd, text, percent_pos - text);
		if (percent_pos && *(percent_pos + 1) == 'c')
		{
			if (full_text[j][0] == '\0')
			{
				write(fd, full_text[j], 1);
				length++;
			}
		}
		write(fd, full_text[j], ft_strlen(full_text[j]));
		text = percent_pos + 2;
		j++;
	}
	if (text && *text)
		write(fd, text, ft_strlen(text));
	return (count_and_free_all(full_text, arg_count) + length);
}

int	count_and_free_all(char **arg_array, int arg_count)
{
	int		i;
	size_t	length;

	i = 0;
	length = 0;
	while (i < arg_count)
	{
		length += ft_strlen(arg_array[i]);
		free(arg_array[i]);
		i++;
	}
	free(arg_array);
	return (length);
}

char	*ft_strdup_null(const char *str)
{
	size_t	i;
	size_t	length;
	char	*new_str;

	if (!str)
	{
		new_str = malloc(7);
		if (!new_str)
			return (NULL);
		ft_strcpy(new_str, "(null)");
		return (new_str);
	}
	length = ft_strlen((char *)str);
	new_str = (char *)malloc(length + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < length)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
