/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalkhati <lalkhati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 15:38:10 by malsabah          #+#    #+#             */
/*   Updated: 2026/03/30 14:05:28 by lalkhati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_path(t_command *cmd, t_shell *shell);
void		update_pwd(t_shell *shell, char *oldpwd, int oldpwd_status);

static int	print_error(char *cmd, char *message, int status)
{
	write(2, "minishell: ", 11);
	if (cmd)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 2);
	}
	if (message)
		write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	return (status);
}

/* set_env_value and get_env_value moved to builtins/env_helpers.c */

int	ft_cd(t_shell *shell, t_command *cmd)
{
	char	*path;
	char	oldpwd[PATH_MAX];
	int		oldpwd_status;

	oldpwd_status = 1;
	if (!getcwd(oldpwd, sizeof(oldpwd)))
		oldpwd_status = 0;
	if (cmd->arg_lst[1] && cmd->arg_lst[2])
		return (print_error("cd", "too many arguments", 1));
	path = get_path(cmd, shell);
	if (!path)
		return (1);
	if (chdir(path) != 0)
	{
		ft_fprintf(2, "minishell: cd: %s: %s\n", path, strerror(errno));
		return (1);
	}
	update_pwd(shell, oldpwd, oldpwd_status);
	return (0);
}

void	update_pwd(t_shell *shell, char *oldpwd, int oldpwd_status)
{
	char	cwd[PATH_MAX];

	if (!getcwd(cwd, sizeof(cwd)))
		ft_fprintf(2, "cd: error retrieving current directory: %s %s",
			"getcwd: cannot access parent directories:",
			"No such file or directory\n");
	else
		set_env_value(shell, "PWD", cwd);
	if (oldpwd_status)
		set_env_value(shell, "OLDPWD", oldpwd);
}

static char	*get_path(t_command *cmd, t_shell *shell)
{
	char	*path;

	path = NULL;
	if (!cmd->arg_lst[1])
	{
		path = get_env_value(shell, "HOME");
		if (!path)
			print_error("cd", "HOME not set", 1);
	}
	else
		path = cmd->arg_lst[1];
	if (path && ft_strlen(path) == 0)
		path = ".";
	else if (ft_strcmp(path, "-") == 0)
		path = get_env_value(shell, "OLDPWD");
	return (path);
}

/*
int	main(int ac, char **av, char **envp)
{
//cc cd.c ../init_shell.c export.c export_utils.c -L ../libft/ -lft
	t_shell    *shell;
	t_cmd      cmd;
	char       cwd[PATH_MAX];

	shell = init_shell(envp);
	getcwd(cwd, sizeof(cwd));
	printf("Before cd: %s\n", cwd);
	cmd.args = malloc(sizeof(char *) * 3);
	cmd.args[0] = ft_strdup("cd");
	cmd.args[1] = ft_strdup("/home/mo/Projects/");
	cmd.args[2] = NULL;

	if (ft_cd(shell, &cmd) == 0)
		printf("cd ok\n");
	else
		printf("cd ko\n");

	getcwd(cwd, sizeof(cwd));
	printf("After cd:  %s\n", cwd);
	free(cmd.args[0]);
	free(cmd.args[1]);
	free(cmd.args);
	free_env(shell);

	return (0);
}*/
