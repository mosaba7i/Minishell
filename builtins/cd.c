/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 15:38:10 by malsabah          #+#    #+#             */
/*   Updated: 2026/02/18 14:42:12 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int print_error(char *cmd, char *message, int status)
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

static t_env *find_env(t_env *env, char *key)
{
    while (env)
    {
        if (ft_strncmp(env->key, key, ft_strlen(key) + 1) == 0)
            return (env);
        env = env->next;
    }
    return (NULL);
}

static void    set_env_value(t_shell *shell, char *key, char *value)
{
    t_env   *node;

    if (!key || !shell)
        return ;
    node = find_env(shell->env, key);
    if (node)
    {
        free(node->value);
        if (value)
            node->value = ft_strdup(value);
        else
            node->value = NULL;
    }
    else
    {
        t_env *new = malloc(sizeof(t_env));
        if (!new)
            return ;
        new->key = ft_strdup(key);
        if (value)
            new->value = ft_strdup(value);
        else
            new->value = NULL;
        new->next = shell->env;
        shell->env = new;
    }
}

static char *get_env_value(t_shell *shell, char *key)
{
    t_env *tmp;

    tmp = shell->env;
    while (tmp)
    {
        if (ft_strncmp(tmp->key, key, ft_strlen(key) + 1) == 0)
            return (tmp->value);
        tmp = tmp->next;
    }
    return (NULL);
}

int	ft_cd(t_shell *shell, t_cmd *cmd)
{
	char	*path;
	char	cwd[PATH_MAX]; //this header has a max len of char for paths which is 4096 in linux..

	if (!cmd->args[1])
		path = get_env_value(shell, "HOME");
	else
		path = cmd->args[1];
	if (chdir(path) != 0)
	{
		print_error("cd", strerror(errno), 1);
		return (1);
	}
	getcwd(cwd, sizeof(cwd));
	set_env_value(shell, "PWD", cwd);
	return (0);
}


/*
int main(int ac, char **av, char **envp)
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
