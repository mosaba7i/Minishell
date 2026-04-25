/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 18:53:09 by malsabah          #+#    #+#             */
/*   Updated: 2026/04/21 18:57:25 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	if (!s1 || !s2)
		return (1);
	while ((unsigned char)s1[i] != '\0'
		&& (unsigned char)s2[i] == (unsigned char)s1[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	print_error_free(t_shell *shell, const char *msg)
{
	perror(msg);
	if (shell)
	{
		if (shell->ptrs)
			free_ptrs(shell->ptrs->tokens, shell->ptrs->commands);
		if (shell->fd_to_close != -1)
			close(shell->fd_to_close);
		free_env(shell);
	}
	rl_clear_history();
	if (errno)
		exit(errno);
	else
		exit(1);
}

void	free_tokens(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->value);
		free(tmp);
	}
}

void	free_commands(t_command *head)
{
	t_command	*tmp;
	t_redir		*redir_tmp;
	int			i;

	while (head)
	{
		tmp = head;
		head = head->next;
		i = 0;
		while (tmp->arg_lst && tmp->arg_lst[i])
			free(tmp->arg_lst[i++]);
		free(tmp->arg_lst);
		while (tmp->redirs)
		{
			redir_tmp = tmp->redirs;
			tmp->redirs = tmp->redirs->next;
			free(redir_tmp->file);
			if (redir_tmp->type == HEREDOC && redir_tmp->fd >= 0)
				close(redir_tmp->fd);
			free(redir_tmp);
		}
		free(tmp);
	}
}

void	*free_ptrs(t_token *tokens, t_command *cmds)
{
	if (tokens)
		free_tokens(tokens);
	if (cmds)
		free_commands(cmds);
	tokens = NULL;
	cmds = NULL;
	return (NULL);
}
