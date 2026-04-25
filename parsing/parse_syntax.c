/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:41:46 by malsabah          #+#    #+#             */
/*   Updated: 2026/04/21 14:53:42 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_redirection(char *str, int num)
{
	if (str)
		return (!ft_strncmp(str, "<<", 3) || !ft_strncmp(str, ">>", 3)
			|| !ft_strncmp(str, "<", 2) || !ft_strncmp(str, ">", 2));
	else
		return (num == REDIR_IN || num == REDIR_OUT || num == REDIR_OUT_APP
			|| num == HEREDOC);
}

int	is_operator_num(int num)
{
	return (num == REDIR_IN || num == REDIR_OUT || num == REDIR_OUT_APP
		|| num == HEREDOC || num == PIPE);
}

int	check_syntax(t_token *tokens, t_shell *shell)
{
	t_token	*prev;

	if (!tokens)
		return (0);
	prev = tokens;
	tokens = tokens->next;
	if (prev->type == PIPE)
		return (print_error_syntax(NULL, "|", shell));
	while (tokens)
	{
		if (is_redirection(NULL, prev->type) && is_operator_num(tokens->type))
			return (print_error_syntax(NULL, tokens->value, shell));
		if (prev->type == PIPE && tokens->type == PIPE)
			return (print_error_syntax(NULL, "|", shell));
		prev = tokens;
		tokens = tokens->next;
	}
	if (!tokens && is_operator_num(prev->type))
		return (print_error_syntax(
				"syntax error near unexpected token `newline'",
				prev->value, shell));
	return (0);
}

int	print_error_syntax(char *msg, char *str, t_shell *shell)
{
	shell->exit_status = 2;
	write(2, "minishell: ", 11);
	if (msg)
		write(2, msg, ft_strlen(msg));
	else
		ft_fprintf(2, "syntax error near unexpected token `%s'", str);
	write(2, "\n", 1);
	return (-1);
}
