
#include "minishell.h"

void print_commands(t_commnad *head);
void print_tokens(t_token *head);
void debug_print_heredocs(t_redir *redir_list);

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
		// print_tokens(tokens);

		t_commnad *cmds = parse(tokens);
		// print_commands(cmds);

		handle_heredoc(cmds);
		// debug_print_heredocs(cmds->redirs);
		// execute(cmds);

		// free_all(tokens, cmds, line);
		free(inpt_line);
	}
}

// TODO: remove before turn in
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

// TODO: remove before turn in
void print_commands(t_commnad *head)
{
	printf("------------------------------------------\n");
	printf("------------------------------------------\n");
	while (head)
	{
		printf("Args: \n[");
		int i = 0;
		while (head->arg_lst[i])
			printf("%s, ", head->arg_lst[i++]);
		printf("NULL]  \n");
		printf("redirections:  \n");
		while (head->redirs)
		{
			printf("file: %s type: %d ", head->redirs->file, head->redirs->type);
			if (head->redirs->type == 2)
				printf(" %s\n", "REDIR_IN");
			else if (head->redirs->type == 3)
				printf(" %s\n", "REDIR_OUT");
			else if (head->redirs->type == 4)
				printf(" %s\n", "REDIR_OUT_APP");
			else if (head->redirs->type == 5)
				printf(" %s\n", "HEREDOC");
			head->redirs = head->redirs->next;
		}
		head = head->next;
	}
}

// TODO: remove before turn in
static void dump_fd_contents(int fd)
{
	int dup_fd;
	ssize_t r;
	char buf[256];

	dup_fd = dup(fd);
	if (dup_fd == -1)
	{
		perror("dup");
		return;
	}

	dprintf(2, "----- HEREDOC FD %d CONTENT START -----\n", fd);

	while ((r = read(dup_fd, buf, sizeof(buf))) > 0)
		write(2, buf, r);

	if (r == -1)
		perror("read");

	dprintf(2, "\n----- HEREDOC FD %d CONTENT END -----\n", fd);

	close(dup_fd);
}
// TODO: remove before turn in
void debug_print_heredocs(t_redir *redir_list)
{
	int i = 0;

	while (redir_list)
	{
		if (redir_list->type == HEREDOC)
		{
			dprintf(2, "\n Checking heredoc #%d (fd=%d)\n",
					i, redir_list->fd);

			dump_fd_contents(redir_list->fd);
			i++;
		}
		redir_list = redir_list->next;
	}

	if (i == 0)
		dprintf(2, "No heredocs found.\n");
}