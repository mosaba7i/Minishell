/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 13:28:20 by lalkhati          #+#    #+#             */
/*   Updated: 2026/04/21 20:50:43 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sign;

void		print_tokens(t_token *head);
void		debug_print_heredocs(t_redir *redir_list);
void		print_heredocs(t_command *head);
void		print_commands(t_command *head);
static void	update_last_arg(t_command *cmd, t_shell *shell);

static void	process_command(t_shell *shell, t_command *cmds)
{
	if (handle_heredoc(cmds, shell) == 130)
	{
		shell->exit_status = 130;
		reset_ptrs(shell);
		return ;
	}
	if (check_env_expansion(cmds, shell) == -1)
	{
		shell->exit_status = 1;
		reset_ptrs(shell);
		return ;
	}
	handle_quotes(cmds, shell);
	update_last_arg(cmds, shell);
	execute(shell, cmds);
	reset_ptrs(shell);
}

static char	*read_input(t_shell *shell)
{
	char	*prompt;
	char	*pwd;
	char	*inpt_line;

	initsig_prompt();
	pwd = get_env_value(shell, "PWD");
	if (!pwd)
		pwd = "minishell";
	prompt = ft_strjoin(pwd, "$ ");
	if (!prompt)
		print_error_free(shell, "minishell: malloc");
	inpt_line = readline(prompt);
	free(prompt);
	if (g_sign == 2)
		shell->exit_status = 130;
	shell->is_parent = TRUE;
	if (!inpt_line)
		ft_exit(shell, NULL);
	if (*inpt_line)
		add_history(inpt_line);
	return (inpt_line);
}

static void	run_shell_loop(t_shell *shell)
{
	char		*inpt_line;
	t_token		*tokens;
	t_command	*cmds;

	while (1)
	{
		inpt_line = read_input(shell);
		tokens = tokenize(inpt_line, shell);
		free(inpt_line);
		cmds = parse(tokens, shell);
		process_command(shell, cmds);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	(void)argc;
	(void)argv;
	shell = init_shell(envp);
	if (!shell)
		return (1);
	run_shell_loop(shell);
	return (0);
}

static void	update_last_arg(t_command *cmd, t_shell *shell)
{
	int		i;
	char	*path;

	if (!cmd || !cmd->arg_lst)
		return ;
	if (cmd->next)
		return ;
	i = 0;
	while (cmd->arg_lst[i])
		i++;
	if (i > 0)
	{
		if (i == 1)
		{
			path = get_cmd_path(shell, cmd->arg_lst[0]);
			if (path)
				set_env_value(shell, "_", path);
			else
				set_env_value(shell, "_", cmd->arg_lst[0]);
			free(path);
			return ;
		}
		set_env_value(shell, "_", cmd->arg_lst[i - 1]);
	}
}
