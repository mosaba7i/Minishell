/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:42:38 by malsabah          #+#    #+#             */
/*   Updated: 2026/04/21 14:42:39 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_operator(char *input, int word)
{
	if (!ft_strncmp(input, "<<", 2) || !ft_strncmp(input, ">>", 2))
		word += 2;
	else
		word++;
	return (word);
}

int	extract_word(char *input, t_shell *shell, int i)
{
	char	inside_qoute;
	size_t	word;

	word = i;
	if (is_operator_char(input[word]))
		return (get_operator(&input[word], word));
	inside_qoute = 0;
	while (input[word])
	{
		if (!inside_qoute && is_operator_char(input[word]))
			break ;
		else if (!inside_qoute && (input[word] == '\'' || input[word] == '\"'))
			inside_qoute = input[word];
		else if (!inside_qoute && is_white_space(input[word]))
			break ;
		else if (inside_qoute && input[word] == inside_qoute)
			inside_qoute = 0;
		word++;
	}
	if (inside_qoute)
		return (print_error_syntax("no end of quote", 0, shell));
	return (word);
}
