/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:41:37 by malsabah          #+#    #+#             */
/*   Updated: 2026/04/21 14:41:39 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_args(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens && tokens->type != PIPE)
	{
		if (is_redirection(tokens->value, 0))
		{
			tokens = tokens->next->next;
			continue ;
		}
		count++;
		tokens = tokens->next;
	}
	return (count);
}

void	get_args(char **args, t_token *tokens, t_shell *shell)
{
	while (tokens && tokens->type != PIPE)
	{
		if (is_redirection(tokens->value, 0))
		{
			tokens = tokens->next->next;
			continue ;
		}
		*args = ft_strdup(tokens->value);
		if (!*args)
			print_error_free(shell, "minishell: malloc");
		tokens = tokens->next;
		(args)++;
	}
	*args = NULL;
}

t_redir	*get_redir(t_token *tokens, t_shell *shell)
{
	t_redir	*current;
	t_redir	*head;

	head = NULL;
	while (tokens && tokens->type != PIPE)
	{
		if (is_redirection(tokens->value, 0))
		{
			current = malloc(sizeof(t_redir));
			if (!current)
				print_error_free(shell, "minishell: malloc");
			current->type = tokens->type;
			current->file = ft_strdup(tokens->next->value);
			if (!current->file)
			{
				free(current);
				print_error_free(shell, "minishell: malloc");
			}
			current->fd = -1;
			append_redir(&head, current);
			tokens = tokens->next;
		}
		tokens = tokens->next;
	}
	return (head);
}

void	append_redir(t_redir **head, t_redir *new)
{
	t_redir	*last;

	new->next = NULL;
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
