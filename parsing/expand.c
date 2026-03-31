#include "../minishell.h"

int is_expandable(char *arg, char *var);
int inside_single_qoutes(char *arg, char *var_pos);
int is_var_between(char **start_quote, char **end_quote, char *var);
void get_var(char *var_pos, char **var, t_shell *shell);
void free_pointers(const int pointer_count, ...);
void replace_var(char *new_arg, char *env_value, char *arg, char *var);
void expand_var(char *var, char **arg, t_shell *shell);
int get_new_arg_len(char *arg, char *var, char *env_value);
void search_var(t_command *cmds, t_shell *shell, int i);
int inside_qoutes(char *arg, char *var);
int is_tilde(char *var);
void get_tilde_value(char *var, char **env_value, t_shell *shell);
void search_tilde(t_command *cmds, t_shell *shell, int i);
char *get_num(char *var, t_shell *shell);
void shift_args(char **arg_lst, int index);
void print_args(char **args);
char *get_expand_value(char *var, t_shell *shell);
static char *get_env_expand_value(char *var, t_shell *shell);

void check_env_expansion(t_command *cmds, t_shell *shell)
{
	int i;

	while (cmds)
	{
		i = 0;
		while (cmds->arg_lst[i])
		{
			search_var(cmds, shell, i);
			if (ft_strlen(cmds->arg_lst[i]) == 0)
			{
				shift_args(cmds->arg_lst, i);
				continue;
			}
			search_tilde(cmds, shell, i);
			i++;
		}
		cmds = cmds->next;
	}
}

// TODO: remove print_args before turn in
void print_args(char **args)
{
	int i = 0;
	printf("Args: \n");
	while (args[i])
	{
		printf("%s\n", args[i]);
		i++;
	}
}

void shift_args(char **arg_lst, int index)
{
	int i;

	free(arg_lst[index]);
	i = index;
	while (arg_lst[i])
	{
		arg_lst[i] = arg_lst[i + 1];
		i++;
	}
}

void search_var(t_command *cmds, t_shell *shell, int i)
{
	char *pos;
	char *var;

	var = NULL;
	pos = ft_strchr(cmds->arg_lst[i], '$');
	while (pos)
	{
		get_var(pos, &var, shell);
		if (var && is_expandable(cmds->arg_lst[i], var))
		{
			expand_var(var, &cmds->arg_lst[i], shell);
			pos = ft_strchr(cmds->arg_lst[i], '$'); // since we overwritten and freed arg, pos point to garbage
			continue;
		}
		pos = ft_strchr(pos + 1, '$');
	}
}

void search_tilde(t_command *cmds, t_shell *shell, int i)
{
	char *var;

	if (cmds->arg_lst[i][0] != '~')
		return;
	var = NULL;
	get_var(cmds->arg_lst[i], &var, shell);
	expand_var(var, &cmds->arg_lst[i], shell);
}

void get_var(char *var_pos, char **var, t_shell *shell)
{
	int i;

	if (var_pos[1] == '?' || ft_isdigit(var_pos[1]) || is_tilde(var_pos))
	{
		if (var_pos[1] == '\0' || var_pos[1] == '/' || var_pos[1] == ':')
			*var = ft_substr(var_pos, 0, 1);
		else
			*var = ft_substr(var_pos, 0, 2);
	}
	else
	{
		i = 1;
		while (var_pos[i])
		{
			if (var_pos[0] == '$' && !ft_isalnum(var_pos[i]) && var_pos[i] != '_')
				break;
			i++;
		}
		*var = ft_substr(var_pos, 0, i);
	}
	if (!*var)
		print_error_free(shell, "minishell: malloc");
}

int is_expandable(char *arg, char *var)
{
	if (!ft_strncmp(var, "$", 2) || inside_single_qoutes(arg, var)) // $ is on its own in the arg and is between single qoutes
	{
		free(var);
		return (0);
	}
	if (!ft_strncmp(arg, var, ft_strlen(arg))) // var is on its own in the arg
		return (1);
	if (!ft_strncmp(var, "~", 1) && inside_qoutes(arg, var))
	{
		free(var);
		return (0);
	}
	if (!ft_strncmp(var, "$?", 3))
		return (1);
	return (1);
}

int is_tilde(char *var)
{
	if (var[0] != '~')
		return (0);
	if (var[1] == '\0' || var[1] == '/' || var[1] == ':')
		return (1);
	else if (var[1] == '0' || var[1] == '-' || var[1] == '+')
	{
		if (var[2] == '\0' || var[2] == '/' || var[2] == ':')
			return (1);
	}
	return (0);
}

int inside_single_qoutes(char *arg, char *var)
{
	char *start_quote;
	char *end_quote;
	int double_qoute;

	double_qoute = 0;
	assign_null(2, &start_quote, &end_quote);
	while (*arg)
	{
		if (*arg == '\"')
			double_qoute = !double_qoute; // don't care about single qoutes if we are inside double qoutes
		if (*arg == '\'' && !double_qoute)
		{
			if (!start_quote)
				start_quote = arg;
			else if (!end_quote)
				end_quote = arg;
			if (start_quote && end_quote && is_var_between(&start_quote, &end_quote, var))
				return (1);
			else if (start_quote && end_quote) // reset for next qoute, written in a cursed way for norm :)
				assign_null(2, &start_quote, &end_quote);
		}
		arg++;
	}
	return (0);
}

int inside_qoutes(char *arg, char *var)
{
	char *start_quote;
	char *end_quote;
	char inside_qoute;

	inside_qoute = 0;
	assign_null(2, &start_quote, &end_quote);
	while (*arg)
	{
		if (!inside_qoute && (*arg == '\"' || *arg == '\''))
		{
			inside_qoute = *arg;
			start_quote = arg;
		}
		else if (inside_qoute && *arg == inside_qoute)
		{
			inside_qoute = 0;
			end_quote = arg;
		}
		if (start_quote && end_quote && is_var_between(&start_quote, &end_quote, var))
			return (1);
		else if (start_quote && end_quote)
			assign_null(2, &start_quote, &end_quote);
		arg++;
	}
	return (0);
}

// we send pointer to pointer since we want to search position betwen current quotes only.
int is_var_between(char **start_quote, char **end_quote, char *var)
{
	char *exists;

	exists = ft_strnstr(*start_quote, var, *end_quote - *start_quote);
	if (exists)
		return (1);
	return (0);
}

void assign_null(int num, ...)
{
	va_list arguments;
	int i;
	void **current;

	va_start(arguments, num);
	i = 0;
	while (i < num)
	{
		current = va_arg(arguments, void **);
		*current = NULL;
		i++;
	}
	va_end(arguments);
}

void expand_var(char *var, char **arg, t_shell *shell)
{
	char *env_value;
	char *new_arg;
	int new_len;

	env_value = get_expand_value(var, shell);
	new_len = get_new_arg_len(*arg, var, env_value);
	new_arg = ft_calloc(new_len + 1, sizeof(char));
	if (!new_arg)
	{
		free_pointers(2, var, env_value);
		print_error_free(shell, "minishell: malloc");
	}
	replace_var(new_arg, env_value, *arg, var);
	free_pointers(3, *arg, var, env_value);
	*arg = new_arg;
}

// char *get_expand_value(char *var, t_shell *shell)
// {
// 	char *value;

// 	if (var[0] == '$' && !ft_isalpha(var[1]) && var[1] != '_')
// 		value = get_num(var, shell);
// 	else if (var[0] == '~')
// 		get_tilde_value(var, &value, shell);
// 	else
// 	{
// 		value = get_env_value(shell, var + 1);
// 		if (!value) // if the variable doesn't exist in env, we replace it with empty string
// 			value = ft_strdup("");
// 		else if (ft_strcmp(var, "$_") == 0 && !is_path_directory(value))
// 			value = ft_strdup(ft_strrchr(value, '/') + 1);
// 		else
// 			value = ft_strdup(value);
// 	}
// 	if (!value) // malloc fail
// 	{
// 		free(var);
// 		print_error_free(shell, "minishell: malloc");
// 	}
// 	return (value);
// }

char *get_expand_value(char *var, t_shell *shell)
{
	char *value;

	if (var[0] == '$' && !ft_isalpha(var[1]) && var[1] != '_')
		value = get_num(var, shell);
	else if (var[0] == '~')
		get_tilde_value(var, &value, shell);
	else
		value = get_env_expand_value(var, shell);
	if (!value)
	{
		free(var);
		print_error_free(shell, "minishell: malloc");
	}
	return (value);
}

static char *get_env_expand_value(char *var, t_shell *shell)
{
	char *value;
	char *env_value;

	env_value = get_env_value(shell, var + 1);
	if (!env_value)
		return (ft_strdup(""));
	if (ft_strcmp(var, "$_") == 0 && !is_path_directory(env_value))
		return (ft_strdup(ft_strrchr(env_value, '/') + 1));
	value = ft_strdup(env_value);
	return (value);
}

int is_path_directory(const char *path)
{
	struct stat stats;

	if (stat(path, &stats) == 0 && S_ISDIR(stats.st_mode))
		return 1;

	return 0;
}

char *get_num(char *var, t_shell *shell)
{
	if (var[0] == '$' && var[1] >= '0' && var[1] <= '9')
		return (ft_strdup(""));
	else if (var[1] == '?')
		return (ft_itoa(shell->exit_status));
	return (NULL);
}

void get_tilde_value(char *var, char **env_value, t_shell *shell)
{
	char *temp;
	if (var[1] == '\0' || var[1] == '/' || var[1] == ':')
		temp = get_env_value(shell, "HOME");
	else if ((var[1] == '+' || var[1] == '0') && (var[2] == '\0' || var[2] == '/' || var[2] == ':'))
		temp = get_env_value(shell, "PWD");
	else if (var[1] == '-' && (var[2] == '\0' || var[2] == '/' || var[2] == ':'))
		temp = get_env_value(shell, "OLDPWD");
	else if (ft_strcmp(var + 1, get_env_value(shell, "USER")) == 0)
		temp = get_env_value(shell, "HOME");
	else
		temp = var;
	if (!temp)
		temp = "";
	*env_value = ft_strdup(temp);
}

void replace_var(char *new_arg, char *env_value, char *arg, char *var)
{
	int i;
	int new_len;
	char *var_pos;

	new_len = get_new_arg_len(arg, var, env_value);
	var_pos = ft_strnstr(arg, var, ft_strlen(arg));
	i = 0;
	while (i < new_len)
	{
		if (arg == var_pos)
		{
			if (env_value)
			{
				ft_strlcat(new_arg, env_value, new_len);
				i += ft_strlen(env_value) - 1;
			}
			else
				i--;
			arg += ft_strlen(var) - 1;
		}
		else
			new_arg[i] = (*arg);
		arg++;
		i++;
	}
}

void free_pointers(const int pointer_count, ...)
{
	va_list arguments;
	int i;

	va_start(arguments, pointer_count);
	i = 0;
	while (i < pointer_count)
	{
		free(va_arg(arguments, void *));
		i++;
	}
	va_end(arguments);
}

int get_new_arg_len(char *arg, char *var, char *env_value)
{
	int new_len;

	if (!env_value)
		new_len = ft_strlen(arg) - ft_strlen(var);
	else
		new_len = ft_strlen(arg) - ft_strlen(var) + ft_strlen(env_value);
	return (new_len + 1);
}
