/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_types.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:42:30 by malsabah          #+#    #+#             */
/*   Updated: 2026/04/21 14:42:32 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_type	get_token_type(char *value)
{
	if (!value || !value[0])
		return (WORD);
	if (!ft_strncmp(value, "<<", 3))
		return (HEREDOC);
	if (!ft_strncmp(value, ">>", 3))
		return (REDIR_OUT_APP);
	if (!ft_strncmp(value, "<", 2))
		return (REDIR_IN);
	if (!ft_strncmp(value, ">", 2))
		return (REDIR_OUT);
	if (!ft_strncmp(value, "|", 2))
		return (PIPE);
	return (WORD);
}

void	assign_token_types(t_token *head)
{
	t_token	*current;

	current = head;
	while (current)
	{
		current->type = get_token_type(current->value);
		current = current->next;
	}
}

int	is_white_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	is_operator_char(char c)
{
	return (c == '<' || c == '>' || c == '|');
}
