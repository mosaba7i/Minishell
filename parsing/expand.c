#include "../minishell.h"

int is_expandable(char *arg, char *var);
int inside_single_qoutes(char *arg, char *var_pos);
int is_var_between(char **start_quote, char **end_quote, char *var);
void get_var(char *var_pos, char **var, t_shell *shell);
void free_pointers(const int pointer_count, ...);
void replace_var(char *new_arg, char *env_value, char *arg, char *var);
void expand_var(char *var, char **arg, t_shell *shell);
int get_new_arg_len(char *arg, char *var, char *env_value);

void check_env_expansion(t_command *cmds, t_shell *shell)
{
	int i;
	char *pos;
	char *var;

	while (cmds)
	{
		i = 0;
		while (cmds->arg_lst[i])
		{
			pos = ft_strchr(cmds->arg_lst[i], '$');
			while (pos)
			{
				get_var(pos, &var, shell);
				if (is_expandable(cmds->arg_lst[i], var))
				{
					expand_var(var, &cmds->arg_lst[i], shell);
					pos = ft_strchr(cmds->arg_lst[i], '$'); // since we overwritten and freed arg, pos point to garbage
					continue;
				}
				pos = ft_strchr(pos + 1, '$');
			}
			i++;
		}
		cmds = cmds->next;
	}
}

void get_var(char *var_pos, char **var, t_shell *shell)
{
	int i;

	i = 1;

	if (var_pos[1] == '?')
	{
		*var = ft_substr(var_pos, 0, 2);
		if (!var)
			print_error(shell, "minishell: malloc");
		return;
	}
	while (var_pos[i])
	{
		if (!ft_isalnum(var_pos[i]) && var_pos[i] != '_')
			break;
		i++;
	}
	*var = ft_substr(var_pos, 0, i);
	if (!var)
		print_error(shell, "minishell: malloc");
}

int is_expandable(char *arg, char *var)
{
	if (!ft_strncmp(arg, var, ft_strlen(arg))) // var is on its own in the arg
		return (1);
	if (!ft_strncmp(var, "$", 2) || inside_single_qoutes(arg, var))
	{
		free(var);
		return (0);
	}
	if (!ft_strncmp(var, "$?", 3))
		return (1);
	return (1);
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
	int i;
	char *new_arg;
	int new_len;

	if (!ft_strncmp(var, "$?", 3))
		// TODO: get exit status after execution
		env_value = ft_itoa(999);
	else
		env_value = getenv(var + 1);
	new_len = get_new_arg_len(*arg, var, env_value);
	new_arg = ft_calloc(new_len + 1, sizeof(char));
	if (!new_arg)
	{
		free(var);
		print_error(shell, "minishell: malloc");
	}
	replace_var(new_arg, env_value, *arg, var);
	free_pointers(2, *arg, var);
	*arg = new_arg;
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
	// new_arg[i] = '\0'; ft_calloc already set it to null, i removed it for norm
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
