/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bad_input_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 01:29:31 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/20 16:40:16 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_token_length(char *to_parse)
{
	size_t	i;
	int		len;

	i = -1;
	len = 0;
	while (to_parse[++i] && ft_strchr(DELIM_TOKEN_SP, to_parse[i]))
		len++;
	if (len > 1 && to_parse[i - 1] == ';')
		return (1);
	else if (len > 2)
		return (1);
	return (0);
}

int	check_validity(char *to_parse, size_t i)
{
	int	flags;
	int	am_i_alone;
	int	token;

	token = to_parse[i];
	if (check_function(to_parse, i))
		return (-1);
	am_i_alone = check_behind(to_parse, i);
	if (am_i_alone && (token != '<' && token != '>'))
		return (-1);
	if (!ft_strchr(FORMAT_TOKEN, token))
		return (++i);
	flags = check_in_front(to_parse, token, &i);
	if ((to_parse[i] && flags == -1)
		|| (ft_strchr(R_COMBO, token) && flags == -1))
		return (-1);
	else if (to_parse[i] == 0 && !ft_strchr(R_COMBO, token))
		return (-2);
	return (i);
}

int	check_token_(char token, int *flags, size_t *i)
{
	if ((*flags) > 0)
	{
		*i = *flags - 1;
		return (0);
	}
	if (*flags == -1)
		*flags = token;
	return (-1);
}

int	valid_format_token(char *to_parse)
{
	size_t	i;
	int		flags;
	int		_open;

	i = -1;
	_open = 0;
	while (to_parse[++i])
	{
		flags = 0;
		if (valid_double(to_parse, i) || to_parse[i] == '\'')
			skip_(to_parse, &i, to_parse[i]);
		if ((to_parse[i] == '(' || to_parse[i] == ')')
			&& valid_parentheses(to_parse, &_open, i) < 0)
			return (')');
		if (to_parse[i] && !ft_isspace(to_parse[i]))
			flags = check_validity(to_parse, i);
		if (flags && check_token_(to_parse[i], &flags, &i) < 0)
			return (flags);
		if (to_parse[i] == 0)
			break ;
	}
	if (_open)
		return (')');
	return (0);
}

int	unvalid_line(t_data *data, char *line, char **rescue_cmd)
{
	int		err;
	char	*tmp;

	err = valid_format_token(line);
	if (err > 0)
		print_bad_syntax(data, TOKEN_SYNTAX_ERR, err);
	else if (err == -2)
		rescue_command(data, rescue_cmd, err);
	if ((*rescue_cmd))
	{
		tmp = (*rescue_cmd);
		(*rescue_cmd) = ft_strjoin(data -> cp_to_parse, (*rescue_cmd), 0, 0);
		is_error(data, (*rescue_cmd), MALLOC_ERR, 0);
		ft_free_elem((void **)&data -> cp_to_parse);
		ft_free_elem((void **)&tmp);
		data -> cp_to_parse = (*rescue_cmd);
		(*rescue_cmd) = NULL;
		return (0);
	}
	return (err);
}
