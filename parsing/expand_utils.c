/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:38:11 by malsabah          #+#    #+#             */
/*   Updated: 2026/04/21 14:38:12 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_tilde(char *var)
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

int	inside_single_qoutes(char *arg, char **var_pos)
{
	char	*start_quote;
	char	*end_quote;
	int		double_qoute;

	double_qoute = 0;
	assign_null(2, &start_quote, &end_quote);
	while (*arg)
	{
		if (*arg == '\"' && !start_quote)
			double_qoute = !double_qoute;
		if (*arg == '\'' && !double_qoute)
		{
			if (!start_quote)
				start_quote = arg;
			else if (!end_quote)
				end_quote = arg;
			if (start_quote && end_quote && is_var_between(&start_quote,
					&end_quote, var_pos))
				return (1);
			else if (start_quote && end_quote)
				assign_null(2, &start_quote, &end_quote);
		}
		arg++;
	}
	return (0);
}

static int	check_quotes(char *arg, char **var_pos, struct s_quote_state *state)
{
	if (!state->inside_quote && (*arg == '"' || *arg == '\''))
	{
		state->inside_quote = *arg;
		state->start_quote = arg;
	}
	else if (state->inside_quote && *arg == state->inside_quote)
	{
		state->inside_quote = 0;
		state->end_quote = arg;
	}
	if (state->start_quote && state->end_quote
		&& is_var_between(&state->start_quote, &state->end_quote, var_pos))
		return (1);
	else if (state->start_quote && state->end_quote)
	{
		state->start_quote = NULL;
		state->end_quote = NULL;
	}
	return (0);
}

int	inside_qoutes(char *arg, char **var_pos)
{
	struct s_quote_state	state;

	state.inside_quote = 0;
	state.start_quote = NULL;
	state.end_quote = NULL;
	while (*arg)
	{
		if (check_quotes(arg, var_pos, &state))
			return (1);
		arg++;
	}
	return (0);
}

int	is_var_between(char **start_quote, char **end_quote, char **var_pos)
{
	if (*start_quote == *end_quote)
		return (0);
	if (*var_pos < *start_quote || *var_pos > *end_quote)
		return (0);
	else if (*var_pos > *start_quote && *var_pos < *end_quote)
		return (1);
	return (0);
}
