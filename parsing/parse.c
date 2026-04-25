/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:41:52 by malsabah          #+#    #+#             */
/*   Updated: 2026/04/21 14:41:53 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_command	*new_command(t_shell *shell)
{
	t_command	*list_node;

	list_node = malloc(sizeof(t_command));
	if (!list_node)
		print_error_free(shell, "minishell: malloc");
	list_node->next = NULL;
	list_node->arg_lst = NULL;
	list_node->redirs = NULL;
	return (list_node);
}

static void	append_command(t_command **head, t_command *new)
{
	t_command	*last;

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

t_command	*parse(t_token *tokens, t_shell *shell)
{
	t_command	*head;
	t_command	*current_cmd;

	if (check_syntax(tokens, shell) == -1)
		return (NULL);
	head = NULL;
	while (tokens)
	{
		current_cmd = new_command(shell);
		append_command(&head, current_cmd);
		shell->ptrs->commands = head;
		current_cmd->arg_lst = malloc((count_args(tokens) + 1)
				* sizeof(char *));
		if (!current_cmd->arg_lst)
			print_error_free(shell, "minishell: malloc");
		get_args(current_cmd->arg_lst, tokens, shell);
		current_cmd->redirs = get_redir(tokens, shell);
		while (tokens && tokens->type != PIPE)
			tokens = tokens->next;
		if (tokens)
			tokens = tokens->next;
	}
	return (head);
}
