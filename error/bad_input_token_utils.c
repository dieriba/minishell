/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bad_input_token_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 20:02:02 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/29 21:22:48 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	skip_(char *to_parse, size_t *i, int quote)
{
	size_t	j;

	j = (*i);
	while (1)
	{
		while (to_parse[++j] && to_parse[j] != quote)
			;
		if (to_parse[j + 1] == '\'' || to_parse[j + 1] == '"')
			quote = to_parse[++j];
		else
			break ;
	}
	(*i) = j;
}

void	skip_reverse(char *to_parse, int *i, int quote)
{
	int	j;

	j = (*i);
	while (1)
	{
		while (--j > -1 && to_parse[j] != quote)
			;
		if (j >= 0 && (to_parse[j - 1] == '\'' || to_parse[j - 1] == '"'))
			quote = to_parse[--j];
		else
			break ;
	}
	(*i) = j;
}

void	handle_case(t_data *data, char **rescue_cmd, char **cmd, int err)
{
	char	*to_free;

	ft_free_elem((void **)cmd);
	if (err == 2)
		print_bad_syntax(data, TOKEN_EOF_ERR, err);
	else if (err > 2)
		print_bad_syntax(data, TOKEN_SYNTAX_ERR, err);
	if (err > 0)
	{
		to_free = data -> cp_to_parse;
		data -> cp_to_parse = ft_strjoin(data -> cp_to_parse, (*rescue_cmd));
		is_error(data, data -> cp_to_parse, MALLOC_ERR, 0);
		ft_free_elem((void **)rescue_cmd);
		ft_free_elem((void **)&to_free);
	}
}

void	rescue_command(t_data *data, char **rescue_cmd, int err)
{
	char	*cmd;
	char	*to_free;

	while (1)
	{
		cmd = readline("cmd: ");
		err = valid_format_token(cmd);
		if (cmd)
		{
			to_free = (*rescue_cmd);
			(*rescue_cmd) = ft_strjoin((*rescue_cmd), cmd);
			is_error(data, (*rescue_cmd), MALLOC_ERR, 0);
		}
		ft_free_elem((void **)&to_free);
		if (cmd == NULL || err == 0 || err > 0)
			break ;
	}
	handle_case(data, rescue_cmd, &cmd, err);
}

int	check_behind(char *to_parse, int j)
{
	int	seen;
	
	if (to_parse[j] == '(' && j == 0)
		return (j);
	if (!ft_strchr(STOP_, to_parse[j])
		&& (to_parse[j] != '(' && to_parse[j] != ')'))
		return (0);
	seen = 1;
	if (j - 1 < 0)
		return (seen);
	if (to_parse[j] == '(' || to_parse[j] == ')')
		return (check_behind_par(to_parse, j));
	while (--j > -1 && ft_strchr(DELIM_TOKEN_SP, to_parse[j]))
		;
	while (j > -1 && ft_isspace(to_parse[j]))
		j--;
	if (!ft_strchr(DELIM_TOKEN_SP, to_parse[j])
		&& to_parse[j] != '(')
		seen = 0;
	return (seen);
}
