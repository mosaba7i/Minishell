
#include "minishell.h"

int is_white_space(char c);
t_token *new_token(void *content);
int extract_word(char *input, int i);
t_token *tokenize(char *input);
void append_token(t_token **head, t_token *new);
void print_tokens(t_token *head);
void assign_token_types(t_token *head);
int is_operator(char c);
int get_operator(char *input, int word);

int main(int argc, char **argv, char **envp)
{
	while (1)
	{
		char *inpt_line = readline("minishell$ ");
		if (!inpt_line) // ctrl+D
			return (1);
		if (*inpt_line)
			add_history(inpt_line);
		t_token *tokens = tokenize(inpt_line);
		print_tokens(tokens); // TODO: remove when done debugging

		// s_commnad *cmds   = parse(tokens);

		// execute(cmds);

		// free_all(tokens, cmds, line);
	}
}

t_token *tokenize(char *input)
{
	int i = 0;
	t_token *head;
	t_token *current_token;
	int end_pos;

	head = NULL;
	while (input[i])
	{
		while (is_white_space(input[i]))
			i++;
		if (!input[i])
			break;
		end_pos = extract_word(input, i);
		current_token = new_token(ft_substr(input, i, end_pos - i));
		append_token(&head, current_token);
		i = end_pos;
	}
	assign_token_types(head);
	return (head);
}

int is_white_space(char c)
{
	return c == ' ' || (c >= 9 && c <= 13);
}

int is_operator(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

int extract_word(char *input, int i)
{
	char inside_qoute = 0;
	int word;

	word = i;
	if (is_operator(input[word]))
		return get_operator(&input[word], word);
	inside_qoute = 0;
	while (input[word])
	{
		// printf("word: %d character: %c \n", word, input[word]);
		// printf("inside_qoute?  %d  (%c)  white_space? %d \n", inside_qoute, inside_qoute, is_white_space(input[word]));
		if (!inside_qoute && is_operator(input[word]))
			break;
		else if (!inside_qoute && (input[word] == '\'' || input[word] == '\"'))
			inside_qoute = input[word];
		else if (!inside_qoute && is_white_space(input[word]))
			break;
		else if (inside_qoute && input[word] == inside_qoute)
			inside_qoute = 0;
		word++;
	}
	if (inside_qoute)
	{
		printf("\nno end of qoute >:( \n"); // TODO: combine errors into one function
		exit(1);
	}
	return (word);
}

int get_operator(char *input, int word)
{
	// printf("input: %s \n", input);
	if (!ft_strncmp(input, "<<", 2) || !ft_strncmp(input, ">>", 2))
		word += 2;
	else
		word++;
	return word;
}

t_token *new_token(void *content)
{
	t_token *list_node;

	list_node = malloc(sizeof(t_token));
	if (!list_node)
		return (NULL);
	list_node->next = NULL;
	list_node->value = content;
	return (list_node);
}

void append_token(t_token **head, t_token *new)
{
	t_token *last;

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
t_type get_token_type(char *value)
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

void assign_token_types(t_token *head)
{
	t_token *current = head;

	while (current)
	{
		current->type = get_token_type(current->value);
		current = current->next;
	}
}

void print_tokens(t_token *head)
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