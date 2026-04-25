/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalkhati <lalkhati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 13:59:41 by lalkhati          #+#    #+#             */
/*   Updated: 2025/09/18 14:51:59 by lalkhati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FPRINTF_H
# define FT_FPRINTF_H

# include "../libft/libft.h"
# include <stdarg.h>

int		ft_fprintf(const int fd, const char *text, ...);
int		parse_arguments(const char *text, char **full_text, va_list arguments,
			int arg_count);
char	*parse_specifier(char specifier, va_list arguments);
int		process_output(const char *text, char **full_text, int arg_count,
			int fd);
int		count_and_free_all(char **arg_array, int arg_count);
int		num_length(long long num, long long base);
char	*char_to_string(char chara);
char	*ft_address_char(void *addr);
char	*reverse_num(char *num, int i);
char	*num_to_string(char *char_base, long long num, int base);
char	*num_to_string_unsighned(char *char_base, unsigned long long num,
			int base);
char	*ft_strdup_null(const char *str);
char	*ft_strcpy(char *dest, char *src);

#endif
