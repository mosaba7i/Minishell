#include "../minishell.h"

t_command *new_command();
int count_args(t_token *tokens);
int count_redir(t_token *tokens);
void get_args(char **args, t_token *tokens, t_shell *shell);
void append_redir(t_redir **head, t_redir *new);
void append_command(t_command **head, t_command *new);
t_redir *get_redir(t_token *tokens, t_shell *shell);
int is_redirection(char *str, int num);
int is_operator_num(int num);
int check_syntax(t_token *tokens, t_shell *shell);

t_command *parse(t_token *tokens, t_shell *shell)
{
	t_command *head;
	t_command *current_cmd;
	char **args;

	if (check_syntax(tokens, shell) == -1)
		return (NULL);
	head = NULL;
	while (tokens)
	{
		current_cmd = new_command(shell);
		current_cmd->arg_lst = malloc((count_args(tokens) + 1) * sizeof(char *));
		if (!current_cmd->arg_lst)
			print_error(shell, "minishell: malloc");
		get_args(current_cmd->arg_lst, tokens, shell);
		current_cmd->redirs = get_redir(tokens, shell);
		current_cmd->next = NULL;
		append_command(&head, current_cmd);
		shell->ptrs->commands = head; // update shell ptrs for freeing later
		while (tokens && tokens->type != PIPE)
			tokens = tokens->next;
		if (tokens)
			tokens = tokens->next;
	}
	return (head);
}

int check_syntax(t_token *tokens, t_shell *shell)
{
	t_token *prev;

	if (!tokens)
		return (0);
	prev = tokens;
	tokens = tokens->next;
	if (prev->type == PIPE)
		return (print_error_syntax(NULL, "|"));
	while (tokens)
	{
		if (is_redirection(NULL, prev->type) && is_operator_num(tokens->type))
			return (print_error_syntax(NULL, tokens->value));
		if (prev->type == PIPE && tokens->type == PIPE)
			return (print_error_syntax(NULL, "|"));
		prev = tokens;
		tokens = tokens->next;
	}
	if (!tokens && is_operator_num(prev->type))
		return (print_error_syntax(NULL, prev->value));
	return (0);
}

int print_error_syntax(char *msg, char *str)
{
	write(2, "minishell: ", 11);
	if (msg)
		write(2, msg, ft_strlen(msg));
	else
	{
		write(2, "syntax error near unexpected token `", 37);
		write(2, str, ft_strlen(str));
		write(2, "'", 1);
	}
	write(2, "\n", 1);
	return (-1);
}

t_command *new_command(t_shell *shell)
{
	t_command *list_node;

	list_node = malloc(sizeof(t_command));
	if (!list_node)
		print_error(shell, "minishell: malloc");
	list_node->next = NULL;
	list_node->arg_lst = NULL;
	list_node->redirs = NULL;
	return (list_node);
}

int count_args(t_token *tokens)
{
	int count;

	count = 0;
	while (tokens && tokens->type != PIPE)
	{
		if (is_redirection(tokens->value, 0))
		{
			tokens = tokens->next->next;
			continue;
		}
		count++;
		tokens = tokens->next;
	}
	return (count);
}

void get_args(char **args, t_token *tokens, t_shell *shell)
{
	while (tokens && tokens->type != PIPE)
	{
		if (is_redirection(tokens->value, 0))
		{
			tokens = tokens->next->next;
			continue;
		}
		*args = ft_strdup(tokens->value);
		if (!*args)
			print_error(shell, "minishell: malloc");
		tokens = tokens->next;
		*args++;
	}
	*args = NULL;
}

t_redir *get_redir(t_token *tokens, t_shell *shell)
{
	t_redir *current;
	t_redir *head;

	head = NULL;
	while (tokens && tokens->type != PIPE)
	{
		if (is_redirection(tokens->value, 0))
		{
			current = malloc(sizeof(t_redir));
			if (!current)
				print_error(shell, "minishell: malloc");
			current->type = tokens->type;
			current->file = ft_strdup(tokens->next->value);
			if (!current->file)
				print_error(shell, "minishell: malloc");
			current->next = NULL;
			append_redir(&head, current);
			tokens = tokens->next->next;
			continue;
		}
		tokens = tokens->next;
	}
	return (head);
}

void append_redir(t_redir **head, t_redir *new)
{
	t_redir *last;

	if (!(*head))
	{
		*head = new;
		return;
	}
	last = *head;
	while (last->next)
		last = last->next;
	last->next = new;
}

void append_command(t_command **head, t_command *new)
{
	t_command *last;

	if (!(*head))
	{
		*head = new;
		return;
	}
	last = *head;
	while (last->next)
		last = last->next;
	last->next = new;
}

int is_redirection(char *str, int num)
{
	if (str)
		return (!ft_strncmp(str, "<<", 3) || !ft_strncmp(str, ">>", 3) || !ft_strncmp(str, "<", 2) || !ft_strncmp(str, ">", 2));
	else
		return (num == REDIR_IN || num == REDIR_OUT || num == REDIR_OUT_APP || num == HEREDOC);
}

int is_operator_num(int num)
{
	return (num == REDIR_IN || num == REDIR_OUT || num == REDIR_OUT_APP || num == HEREDOC || num == PIPE);
}
