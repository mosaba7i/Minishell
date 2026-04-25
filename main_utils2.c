/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 18:55:30 by malsabah          #+#    #+#             */
/*   Updated: 2026/04/21 18:56:53 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_token *head)
{
	while (head)
	{
		printf("value: [%s]  type: %d ", head->value, head->type);
		if (head->type == 0)
			printf(" %s\n", "WORD");
		if (head->type == 1)
			printf(" %s\n", "PIPE");
		if (head->type == 2)
			printf(" %s\n", "REDIR_IN");
		if (head->type == 3)
			printf(" %s\n", "REDIR_OUT");
		if (head->type == 4)
			printf(" %s\n", "REDIR_OUT_APP");
		if (head->type == 5)
			printf(" %s\n", "HEREDOC");
		head = head->next;
	}
}

void	reset_ptrs(t_shell *shell)
{
	free_ptrs(shell->ptrs->tokens, shell->ptrs->commands);
	assign_null(2, &shell->ptrs->tokens, &shell->ptrs->commands);
}
