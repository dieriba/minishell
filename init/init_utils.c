/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:52:55 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/02 05:53:06 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_end_string(char *to_parse, int j)
{
	if (to_parse[j] == g_data -> neg_single_start)
		j = calcul_word(to_parse, '\'', j);
	else if (to_parse[j] == g_data -> neg_double_start)
		j = calcul_word(to_parse, '"', j);
	else
		j = calcul_word(to_parse, 0, j);
	return (j);
}

int	skip_spaces(char *to_parse, int i, int skip)
{
	while (to_parse[i] && to_parse[i] == ' ')
		i++;
	if (skip)
	{
		while (to_parse[i] && (to_parse[i] == '"' 
			||  to_parse[i] == '\''))
			i++;
	}
	return (i);
}

int	is_same_token(char c, char d)
{
	if (ft_strchr(FORMAT_TOKEN, c)
		&& ft_strchr(FORMAT_TOKEN, d))
	{
		if (c == d)
			return (1);
	}
	return (0);
}

int	skip_char_in_str(size_t i, char *to_parse, char *to_skip, int opt)
{
	if (opt)
		while (to_parse[i] && is_real_stop(to_parse, i, to_skip))
			i++;
	else
		while (to_parse[i] && ft_strchr(to_skip, to_parse[i]))
			i++;
	return (i);
}

int	count_words(char *to_parse)
{
	size_t	i;
	int		length;

	i = -1;
	length = 0;
	while (to_parse[++i] && is_real_stop(to_parse, i, STOP_))
	{
		i = skip_spaces(to_parse, i, 0);
		if (to_parse[i] == g_data -> neg_double_start)
			i = loop_nested_quote(to_parse, i, g_data -> neg_double_end);
		else if (to_parse[i] == g_data -> neg_single_start)
			i = loop_nested_quote(to_parse, i, g_data -> neg_single_end);
		else if (ft_strchr(R_COMBO, to_parse[i]))
			while (to_parse[i] && to_parse[i] != ' ')
				i++;
		else
		{
			while (to_parse[i] && to_parse[i] != ' ')
				i++;
			length++;
		}
		i = skip_spaces(to_parse, i, 0);
		if (!to_parse[i] || ft_strchr(STOP_, to_parse[i]))
			break ;
	}
	return (length);
}

int	is_real_stop(char *to_parse, size_t i , char *in)
{
	if (ft_strchr(in , to_parse[i]) && !find_end_quotes(to_parse, i))
		return (0);
	return (1);
}

int		calcul_word(char *to_parse, char quote, int j)
{
	if (quote == '\'')
		j = loop_nested_quote(to_parse, j, g_data -> neg_single_end);
	else if (quote == '"')
		j = loop_nested_quote(to_parse, j, g_data -> neg_double_end);
	else
		while (to_parse[j] && !ft_strchr(STOP_F_P, to_parse[j]))
			j++;
	return (j);
}
