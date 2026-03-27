/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalkhati <lalkhati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 14:08:28 by lalkhati          #+#    #+#             */
/*   Updated: 2025/11/09 11:01:44 by lalkhati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

static int check_type(char chara, char *set);
static int count_arg(const char *text);
static int handle_no_percent(const char *text, int length, int fd);

int ft_fprintf(const int fd, const char *text, ...)
{
	va_list arguments;
	int arg_count;
	char **full_text;
	int length;

	length = ft_strlen(text);
	if (!length)
		return (0);
	va_start(arguments, text);
	arg_count = count_arg(text);
	if (arg_count == 0)
		return (handle_no_percent(text, length, fd));
	else if (arg_count == -1)
		return (-1);
	length -= (arg_count * 2);
	full_text = malloc((sizeof(char *) * arg_count) + 1);
	if (!full_text)
		return (-1);
	if (!parse_arguments(text, full_text, arguments, arg_count))
		return (-1);
	va_end(arguments);
	length += process_output(text, full_text, arg_count, fd);
	return (length);
}

static int count_arg(const char *text)
{
	int i;
	int arg_count;

	i = 0;
	arg_count = 0;
	while (text[i])
	{
		if (text[i] == '%')
		{
			if (text[i + 1])
			{
				if (check_type(text[i + 1], "cspdiuxX%"))
					arg_count++;
				else
					return (-1);
				i += 2;
				continue;
			}
			else
				return (-1);
		}
		i++;
	}
	return (arg_count);
}

static int check_type(char chara, char *set)
{
	int i;

	i = 0;
	while (set[i])
	{
		if (chara == set[i])
			return (chara);
		i++;
	}
	return (0);
}

static int handle_no_percent(const char *text, int length, int fd)
{
	char *s;

	s = (char *)text;
	while (*s)
		write(fd, s++, 1);
	return (length);
}
