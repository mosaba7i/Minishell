#include "minishell.h"

t_commnad *new_command();
int count_args(t_token *tokens);
int count_redir(t_token *tokens);
void get_args(char **args, t_token *tokens);
void append_redir(t_redir **head, t_redir *new);
void append_command(t_commnad **head, t_commnad *new);
t_redir *get_redir(t_token *tokens);
int is_redirection(char *str, int num);
int is_operator_num(int num);
int check_syntax(t_token *tokens);
void print_error(int error); // TODO: make a proper error handler

t_commnad *parse(t_token *tokens)
{
	t_commnad *head;
	t_commnad *current_cmd;
	char **args;

	check_syntax(tokens);
	head = NULL;
	while (tokens)
	{
		current_cmd = new_command();
		// int len = (count_args(tokens) + 1);
		current_cmd->arg_lst = malloc((count_args(tokens) + 1) * sizeof(char *));
		if (!current_cmd->arg_lst)
			exit(1);
		get_args(current_cmd->arg_lst, tokens);
		// for (int i = 0; i < len; i++)
		// 	printf("->%s \n", current_cmd->arg_lst[i]);
		current_cmd->redirs = get_redir(tokens);
		current_cmd->next = NULL;
		append_command(&head, current_cmd);
		while (tokens && tokens->type != PIPE)
			tokens = tokens->next;
		if (tokens)
			tokens = tokens->next;
	}
	return (head);
}

int check_syntax(t_token *tokens)
{
	int error;
	t_token *prev;

	if (!tokens)
		return (0);
	error = 0;
	prev = tokens;
	tokens = tokens->next;
	if (prev->type == PIPE)
		error = 1;
	while (tokens)
	{
		if (is_operator_num(prev->type) && is_operator_num(tokens->type))
			error = 2;
		if (error)
			break;
		prev = tokens;
		tokens = tokens->next;
	}
	if (!tokens && is_operator_num(prev->type))
		error = 1;
	if (error)
		print_error(error);
	return (0);
}

void print_error(int error)
{
	if (error == 1)
		printf("operator at improper place\n");
	else if (error == 2)
		printf("2 operators suceeding each other\n");
	else if (error = 3)
		printf("no file given to redirection\n");
	exit(error);
}

t_commnad *new_command()
{
	t_commnad *list_node;

	list_node = malloc(sizeof(t_commnad));
	if (!list_node)
		exit(1); // TODO: handle print error
	if (!list_node)
		return (NULL);
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

void get_args(char **args, t_token *tokens)
{
	while (tokens && tokens->type != PIPE)
	{
		if (is_redirection(tokens->value, 0))
		{
			tokens = tokens->next->next;
			continue;
		}
		*args++ = ft_strdup(tokens->value);
		tokens = tokens->next;
	}
	*args = NULL;
}

t_redir *get_redir(t_token *tokens)
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
				exit(1); // TODO: print error and free
			current->type = tokens->type;
			current->file = tokens->next->value;
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

void append_command(t_commnad **head, t_commnad *new)
{
	t_commnad *last;

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
