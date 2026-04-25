/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_core.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:42:16 by malsabah          #+#    #+#             */
/*   Updated: 2026/04/21 14:42:17 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*new_token(void *content)
{
	t_token	*list_node;

	list_node = malloc(sizeof(t_token));
	if (!list_node)
	{
		free(content);
		return (NULL);
	}
	list_node->next = NULL;
	list_node->value = content;
	return (list_node);
}

void	append_token(t_token **head, t_token *new)
{
	t_token	*last;

	if (!(*head))
	{
		*head = new;
		return ;
	}
	last = *head;
	while (last->next)
		last = last->next;
	last->next = new;
}

t_token	*create_token(char *input, int i, int end_pos, t_shell *shell)
{
	t_token	*current_token;

	current_token = new_token(ft_substr(input, i, end_pos - i));
	if (!current_token)
	{
		free(input);
		print_error_free(shell, "minishell: malloc");
	}
	return (current_token);
}

t_token	*tokenize(char *input, t_shell *shell)
{
	int		i;
	int		end_pos;
	t_token	*head;
	t_token	*current_token;

	head = NULL;
	i = 0;
	while (input[i])
	{
		while (is_white_space(input[i]))
			i++;
		if (!input[i])
			break ;
		end_pos = extract_word(input, shell, i);
		if (end_pos == -1)
			return (NULL);
		current_token = create_token(input, i, end_pos, shell);
		append_token(&head, current_token);
		shell->ptrs->tokens = head;
		i = end_pos;
	}
	assign_token_types(head);
	return (head);
}
