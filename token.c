#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <unistd.h>

#include "minishell.h"


char *qoute_string(char *start);

int main(int argc, char **argv, char **envp)
{

	while (1)
	{
		char *inpt_line = readline("minishell$ ");
		if (!inpt_line) // ctrl+D
			return (1);
		if (*inpt_line)
		{	
			//add_history(inpt_line);
			printf("%s\n", inpt_line);
		}
		//t_token *tokens = tokenize(line);
		//s_commnad *cmds   = parse(tokens);

		//execute(cmds);

		//free_all(tokens, cmds, line);
	}
}

t_token tokenize(char *input)
{
	int i = 0;
	char *words;
	t_token head;
	t_token current;

	words = ft_split(input, ' ');
	current = head;
	while(words[i])
	{
		current.value = NULL;
		if(ft_strncmp(words[i], "|", 2))
			current.type = PIPE;
		else if(ft_strncmp(*words, "<", 2))
			current.type = REDIR_IN;
		else if(ft_strncmp(words[i], ">", 2))
			current.type = REDIR_OUT;
		else if(ft_strncmp(words[i], "<<", 3))
			current.type = HEREDOC;
		if(ft_strncmp(words[i], ">>", 3))
			current.type = REDIR_OUT_APP;
		if(ft_strncmp(words[i], '"', 1))
		{
			current.type = WORD;
			// TODO: multiple qoutation? expansion logic in single/double, skip words until
			// next quotation
			current.value = qoute_string(ft_strrchr(input, '"'));
		}
		else
		{	
			current.type = WORD;
			current.value = ft_strdup(words[i]);
		}
		current = current.next;
		i++;
	}
	// TODO: freeall
	return (head);
}

char *qoute_string(char *start)
{
	char *word;
	int i;

	i = 0;
	while(start[i] && start[i] != "")
		i++;
	if(start[i] == "")
		return ft_substr(start, 0, i);
	else
		return (NULL);
}


