/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bad_input_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 01:29:31 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/27 04:49:39 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_behind(char *to_parse, char *in, int j, int index)
{
	int	seen;

	seen = 1;
	while (--j > index && !ft_strchr(in, to_parse[j]))
	{
		if (!ft_strchr(STOP_F, to_parse[j]))
			seen = 0;
	}
	return (seen);
}

int	check_double(char *to_parse)
{
	size_t	i;

	i = -1;
	while (to_parse[++i])
	{
		if (to_parse[i] == R_IN && to_parse[i + 1] == R_OUT)
			return (to_parse[i]);
		else if (to_parse[i] == R_OUT && to_parse[i + 1] == R_IN)
			return (to_parse[i]);
	}
	return (0);
}

int	check_token_length(char *to_parse)
{
	size_t	i;
	int		len;

	i = -1;
	while (to_parse[++i])
	{
		len = 0;
		if (ft_strchr(FORMAT_TOKEN, to_parse[i]))
		{
			while (ft_strchr(FORMAT_TOKEN, to_parse[++i]))
				len++;
			if (len > 1)
				return (to_parse[i]);
		}
	}
	return (0);
}

int	check_validity(char *to_parse, size_t i, int both)
{
	int	flags;
	int	am_i_alone;

	flags = -1;
	am_i_alone = both;
	if (both)
		am_i_alone = check_behind(to_parse, FORMAT_TOKEN, i, -1);
	if (ft_strchr(FORMAT_TOKEN, to_parse[i + 1])
		&& to_parse[i] == to_parse[i + 1])
		i++;
	while (to_parse[++i] && !ft_strchr(FORMAT_TOKEN, to_parse[i]))
	{
		if (!ft_strchr(FORMAT_TOKEN_SP, to_parse[i]))
		{
			flags = 1;
			break ;
		}
	}
	if (flags == -1 || am_i_alone || !to_parse[i])
		return (-1);
	return (i);
}

int	valid_format_token(char *to_parse)
{
	size_t	i;
	int		flags;

	i = -1;
	while (to_parse[++i])
	{
		flags = 0;
		if (ft_strchr(STOP_, to_parse[i]))
			flags = check_validity(to_parse, i, 1);
		else if (ft_strchr(R_COMBO, to_parse[i]))
			flags = check_validity(to_parse, i, 0);
		if (flags == -1)
			return (to_parse[i]);
		if (flags > 0)
			i = flags;
	}
	return (0);
}

int	is_str_valid(t_data *data, char *to_parse)
{
	int	err;

	err = valid_format_token(to_parse);
	if (err)
		return (print_bad_syntax(data, TOKEN_SYNTAX_ERR, err));
	err = check_double(to_parse);
	if (err)
		return (print_bad_syntax(data, TOKEN_SYNTAX_ERR, err));
	err = check_token_length(to_parse);
	if (err)
		return (print_bad_syntax(data, TOKEN_SYNTAX_ERR, err));
	err = check_parenthese(to_parse);
	if (err)
		return (print_bad_syntax(data, TOKEN_SYNTAX_ERR, err));
	return (0);
}

int	unvalid_line(char **line)
{
	(void)line;	
	return (0);
}