
#include "minishell.h"

void print_tokens(t_token *head);
void debug_print_heredocs(t_redir *redir_list);
void free_commands(t_command *head);
void print_heredocs(t_command *head);
void print_commands(t_command *head);

int main(int argc, char **argv, char **envp)
{
	t_shell *shell;
	char *inpt_line;

	shell = init_shell(envp);
	if (!shell)
		return (1);

	while (1)
	{
		inpt_line = readline("minishell$ ");
		if (!inpt_line) // ctrl+D
			return (1);
		if (*inpt_line)
			add_history(inpt_line);
		t_token *tokens = tokenize(inpt_line, shell);
		print_tokens(tokens);

		t_command *cmds = parse(tokens, shell);
		print_commands(cmds);

		handle_heredoc(cmds, shell);
		print_heredocs(cmds);

		check_env_expansion(cmds, shell);
		printf("after expansion: \n");
		print_commands(cmds);

		handle_quotes(cmds, shell);
		printf("after removing quotes: \n");
		print_commands(cmds);

		// execute(cmds);
		free_all(tokens, cmds);
	}
	return (0);
}

void print_error(t_shell *shell, const char *msg)
{
	perror(msg);
	free_all(shell->ptrs->tokens, shell->ptrs->commands);
	free_env(shell);
	rl_clear_history();
	if (errno)
		exit(errno);
	else
		exit(1);
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
void print_commands(t_command *head)
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
		t_redir *redir = head->redirs;
		while (redir)
		{
			printf("file: %s type: %d ", redir->file, redir->type);
			if (redir->type == 2)
				printf(" %s\n", "REDIR_IN");
			else if (redir->type == 3)
				printf(" %s\n", "REDIR_OUT");
			else if (redir->type == 4)
				printf(" %s\n", "REDIR_OUT_APP");
			else if (redir->type == 5)
				printf(" %s\n", "HEREDOC");
			redir = redir->next;
		}
		head = head->next;
	}
}

// TODO: remove before turn in
void print_heredocs(t_command *head)
{
	int i = 0;
	while (head)
	{
		printf("Command #%d heredocs:\n", i++);
		t_redir *redir = head->redirs;
		while (redir)
		{
			debug_print_heredocs(redir);
			redir = redir->next;
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

void free_tokens(t_token *head)
{
	t_token *tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->value);
		free(tmp);
	}
}

void free_commands(t_command *head)
{
	t_command *tmp;
	int i;

	while (head)
	{
		tmp = head;
		head = head->next;
		i = 0;
		while (tmp->arg_lst[i])
			free(tmp->arg_lst[i++]);
		free(tmp->arg_lst);
		t_redir *redir_tmp;
		while (tmp->redirs)
		{
			redir_tmp = tmp->redirs;
			tmp->redirs = tmp->redirs->next;
			free(redir_tmp->file);
			if (redir_tmp->type == HEREDOC)
				close(redir_tmp->fd);
			free(redir_tmp);
		}
		free(tmp);
	}
}

void *free_all(t_token *tokens, t_command *cmds)
{
	if (tokens)
		free_tokens(tokens);
	if (cmds)
		free_commands(cmds);
	return (NULL);
}
