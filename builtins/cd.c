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

void set_env_value(t_shell *shell, char *key, char *value)
{
    t_env *node;

    if (!key || !shell)
        return;
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
            return;
        new->key = ft_strdup(key);
        if (value)
            new->value = ft_strdup(value);
        else
            new->value = NULL;
        new->next = shell->env;
        shell->env = new;
    }
}

char *get_env_value(t_shell *shell, char *key)
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

int ft_cd(t_shell *shell, t_command *cmd)
{
    char *path;
    char cwd[PATH_MAX]; // this header has a max len of char for paths which is 4096 in linux..
    char oldpwd[PATH_MAX];

    getcwd(oldpwd, sizeof(oldpwd));
    if (cmd->arg_lst[2])
        return (print_error("cd", "too many arguments", 1));
    if (!cmd->arg_lst[1])
        path = get_env_value(shell, "HOME");
    else
        path = cmd->arg_lst[1];
    if (path && ft_strlen(path) == 0)
        path = ".";
    else if (ft_strcmp(path, "-") == 0)
        path = get_env_value(shell, "OLDPWD");
    if (chdir(path) != 0)
    {
        ft_fprintf(2, "minishell: cd: %s: %s\n", path, strerror(errno));
        return (1);
    }
    getcwd(cwd, sizeof(cwd));
    set_env_value(shell, "PWD", cwd);
    set_env_value(shell, "OLDPWD", oldpwd);
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
