#include "../minishell.h"

int is_expandable(char *arg, char *var, char **var_pos);
int inside_single_qoutes(char *arg, char **var_pos);
int is_var_between(char **start_quote, char **end_quote, char **var_pos);
void get_var(char *var_pos, char **var, t_shell *shell);
void free_pointers(const int pointer_count, ...);
void replace_var(char *new_arg, char *env_value, char *arg, char *var);
int get_new_arg_len(char *arg, char *var, char *env_value);
void search_var(t_command *cmds, t_shell *shell, int i);
int inside_qoutes(char *arg, char **var_pos);
int is_tilde(char *var);
void get_tilde_value(char *var, char **env_value, t_shell *shell);
void search_tilde(t_command *cmds, t_shell *shell, int i);
char *get_num(char *var, t_shell *shell);
void shift_args(char **arg_lst, int index);
void print_args(char **args);
char *get_expand_value(char *var, t_shell *shell);
static char *get_env_expand_value(char *var, t_shell *shell);
void split_var(char *arg, t_command *current_cmd, int arg_index, t_shell *shell);
int multiple_redirs_same_file(t_redir *redir);
void search_var_redir(t_redir *redir, t_shell *shell);
int expand_redir(t_redir *redirs, t_shell *shell);
void substitute_expand_char(char *env_value);
void check_export(t_command *cmds, t_shell *shell);

int check_env_expansion(t_command *cmds, t_shell *shell)
{
	int i;

	while (cmds)
	{
		i = 0;
		check_export(cmds, shell);
		while (cmds->arg_lst[i])
		{
			search_var(cmds, shell, i);
			if (ft_strlen(cmds->arg_lst[i]) == 0)
			{
				shift_args(cmds->arg_lst, i);
				continue;
			}
			split_var(cmds->arg_lst[i], cmds, i, shell);
			search_tilde(cmds, shell, i);
			i++;
		}
		if (expand_redir(cmds->redirs, shell) == -1)
			return (-1);
		cmds = cmds->next;
	}
	return (0);
}

int expand_redir(t_redir *redirs, t_shell *shell)
{

	while (redirs)
	{
		search_var_redir(redirs, shell);
		if (multiple_redirs_same_file(redirs))
			return print_error_syntax("ambiguous redirect", redirs->file, shell);
		redirs = redirs->next;
	}
	return (0);
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
		if (*(pos + 1) == '$')
		{
			pos = pos + 1;
			continue;
		}
		get_var(pos, &var, shell);
		if (var && is_expandable(cmds->arg_lst[i], var, &pos))
		{
			expand_var(var, &cmds->arg_lst[i], shell, 1);
			pos = ft_strchr(cmds->arg_lst[i], '$'); // since we overwritten and freed arg, pos point to garbage
			continue;
		}
		pos = ft_strchr(pos + 1, '$');
	}
}

void search_var_redir(t_redir *redir, t_shell *shell)
{
	char *pos;
	char *var;

	if (redir->type == HEREDOC)
		return;
	var = NULL;
	pos = ft_strchr(redir->file, '$');
	while (pos)
	{
		if (*(pos + 1) == '$')
		{
			pos = pos + 1;
			continue;
		}
		get_var(pos, &var, shell);
		if (var && is_expandable(redir->file, var, &pos)) // we don't expand in heredoc redirs
		{
			expand_var(var, &redir->file, shell, 1);
			pos = ft_strchr(redir->file, '$'); // since we overwritten and freed arg, pos point to garbage
			continue;
		}
		pos = ft_strchr(pos + 1, '$');
	}
}

int multiple_redirs_same_file(t_redir *redir)
{
	int i;
	char *file;
	char quote;

	if (redir->type == HEREDOC)
		return (0);
	i = 0;
	file = redir->file;
	quote = 0;
	while (file[i])
	{
		if (file[i] == '\'' || file[i] == '\"')
			quote = file[i];
		else if (quote && file[i] == quote)
			quote = 0;
		else if (!quote && is_white_space(file[i]))
			return (1);
		i++;
	}
	if (i == 0)
		return (1);
	return (0);
}

void search_tilde(t_command *cmds, t_shell *shell, int i)
{
	char *var;

	if (cmds->arg_lst[i][0] != '~')
		return;
	var = NULL;
	get_var(cmds->arg_lst[i], &var, shell);
	expand_var(var, &cmds->arg_lst[i], shell, 1);
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

int is_expandable(char *arg, char *var, char **var_pos)
{
	if (!ft_strcmp(var, "$") || inside_single_qoutes(arg, var_pos)) // $ is on its own in the arg and is between single qoutes
	{
		free(var);
		return (0);
	}
	if (!ft_strncmp(arg, var, ft_strlen(arg))) // var is on its own in the arg
		return (1);
	if (!ft_strncmp(var, "~", 1) && inside_qoutes(arg, var_pos))
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

int inside_single_qoutes(char *arg, char **var_pos)
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
			if (start_quote && end_quote && is_var_between(&start_quote, &end_quote, var_pos))
				return (1);
			else if (start_quote && end_quote) // reset for next qoute, written in a cursed way for norm :)
				assign_null(2, &start_quote, &end_quote);
		}
		arg++;
	}
	return (0);
}

int inside_qoutes(char *arg, char **var_pos)
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
		if (start_quote && end_quote && is_var_between(&start_quote, &end_quote, var_pos))
			return (1);
		else if (start_quote && end_quote)
			assign_null(2, &start_quote, &end_quote);
		arg++;
	}
	return (0);
}

int is_var_between(char **start_quote, char **end_quote, char **var_pos)
{
	if (*start_quote == *end_quote)
		return (0);
	if (*var_pos < *start_quote || *var_pos > *end_quote)
		return (0);
	else if (*var_pos > *start_quote && *var_pos < *end_quote)
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

void expand_var(char *var, char **arg, t_shell *shell, int substitue)
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
	if (substitue)
		substitute_expand_char(env_value);
	replace_var(new_arg, env_value, *arg, var);
	free_pointers(3, *arg, var, env_value);
	*arg = new_arg;
}

void substitute_expand_char(char *env_value)
{
	int i;

	i = 0;
	while (env_value[i])
	{
		if (env_value[i] == '\'')
			env_value[i] = X_SQUOTE;
		else if (env_value[i] == '\"')
			env_value[i] = X_DQUOTE;
		else if (env_value[i] == '$')
			env_value[i] = X_DOLLAR;
		i++;
	}
}

int count_arg_list(char **arg_lst)
{
	int count = 0;

	while (arg_lst[count])
		count++;
	return (count);
}

void free_args(char **arg_lst)
{
	int i = 0;

	while (arg_lst[i])
	{
		free(arg_lst[i]);
		i++;
	}
	free(arg_lst);
}

static int count_splits(char *arg)
{
	int i;
	int split;
	char inside_quote;

	i = 0;
	split = 0;
	inside_quote = 0;
	while (arg[i])
	{
		if (!inside_quote && (arg[i] == '\'' || arg[i] == '"'))
			inside_quote = arg[i];
		else if (inside_quote && arg[i] == inside_quote)
			inside_quote = 0;
		else if (is_white_space(arg[i]) && !inside_quote)
			split++;
		i++;
	}
	return (split);
}

static int find_split_pos(char *arg, int start)
{
	int i;
	char inside_quote;

	i = start;
	inside_quote = 0;
	while (arg[i])
	{
		if (!inside_quote && (arg[i] == '\'' || arg[i] == '"'))
			inside_quote = arg[i];
		else if (inside_quote && arg[i] == inside_quote)
			inside_quote = 0;
		else if (is_white_space(arg[i]) && !inside_quote)
			return (i);
		i++;
	}
	return (i);
}

static void copy_before_split(char **new_lst, char **old_lst, int arg_index)
{
	int i;

	i = 0;
	while (i < arg_index)
	{
		new_lst[i] = ft_strdup(old_lst[i]);
		i++;
	}
}

static void copy_after_split(char **new_lst, char **old_lst, int old_i, int new_i)
{
	while (old_lst[old_i])
	{
		new_lst[new_i] = ft_strdup(old_lst[old_i]);
		old_i++;
		new_i++;
	}
	new_lst[new_i] = NULL;
}

static int fill_split_args(char **new_lst, char *arg, int new_i)
{
	int start;
	int end;

	start = 0;
	while (arg[start])
	{
		while (arg[start] && is_white_space(arg[start]))
			start++;
		if (!arg[start])
			break;
		end = find_split_pos(arg, start);
		new_lst[new_i] = ft_substr(arg, start, end - start);
		new_i++;
		start = end;
	}
	return (new_i);
}

void split_var(char *arg, t_command *current_cmd, int arg_index, t_shell *shell)
{
	char **new_arg_lst;
	int old_count;
	int split_count;
	int new_i;

	split_count = count_splits(arg);
	if (split_count == 0)
		return;
	old_count = count_arg_list(current_cmd->arg_lst);
	new_arg_lst = ft_calloc(old_count + split_count + 1, sizeof(char *));
	if (!new_arg_lst)
		print_error_free(shell, "minishell: malloc");
	copy_before_split(new_arg_lst, current_cmd->arg_lst, arg_index);
	new_i = arg_index;
	new_i = fill_split_args(new_arg_lst, arg, new_i);
	copy_after_split(new_arg_lst, current_cmd->arg_lst, arg_index + 1, new_i);
	free_args(current_cmd->arg_lst);
	current_cmd->arg_lst = new_arg_lst;
}

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
	if (ft_strcmp(var, "$_") == 0 && ft_strrchr(env_value, '/') && !is_path_directory(env_value))
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
	if (ft_strcmp(var, "$0") == 0)
		return (ft_strdup("minishell"));
	else if (var[0] == '$' && var[1] >= '1' && var[1] <= '9')
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
			new_arg[i] = *arg;
		arg++;
		i++;
	}
}
char get_expand_char(char c)
{
	if (c == '\'')
		return (X_SQUOTE);
	else if (c == '\"')
		return (X_DQUOTE);
	else if (c == '$')
		return (X_DOLLAR);
	return (c);
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

void add_qoutes(char *new_arg, char *pos_eq, char *arg, size_t len)
{
	size_t key_len;

	key_len = pos_eq - arg + 1;			   // include '='
	ft_strlcpy(new_arg, arg, key_len + 1); // VAR=
	new_arg[key_len] = '"';
	ft_strlcpy(new_arg + key_len + 1, pos_eq + 1, len - key_len + 1); // RHS
	new_arg[len + 1] = '"';
	new_arg[len + 2] = '\0';
}

void check_export(t_command *cmds, t_shell *shell)
{
	char *pos_eq;
	char *new_arg;
	int i;
	size_t len;

	if (!cmds->arg_lst[0] || ft_strcmp(cmds->arg_lst[0], "export") != 0)
		return;
	i = 0;
	while (cmds->arg_lst[++i])
	{
		pos_eq = ft_strchr(cmds->arg_lst[i], '=');
		if (!pos_eq || !*(pos_eq + 1) || !ft_strchr(pos_eq + 1, '$'))
			continue;
		len = ft_strlen(cmds->arg_lst[i]);
		new_arg = malloc(len + 3);
		if (!new_arg)
		{
			print_error_free(shell, "minishell: malloc");
			return;
		}
		add_qoutes(new_arg, pos_eq, cmds->arg_lst[i], len);
		free(cmds->arg_lst[i]);
		cmds->arg_lst[i] = new_arg;
	}
}
