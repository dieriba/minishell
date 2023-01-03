/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 06:10:50 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/03 18:45:53 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_real_stop(t_data *data, char *to_parse, size_t i, char *in)
{
	if (!to_parse[i])
		return (0);
	if (ft_strchr(in, to_parse[i]) && !find_end_quotes(data, to_parse, i))
		return (0);
	return (1);
}

int	calcul_word(t_data *data, char *to_parse, char quote, int j)
{
	if (quote == '\'')
		j = loop_nested_quote(to_parse, j, data -> neg_single_end);
	else if (quote == '"')
		j = loop_nested_quote(to_parse, j, data -> neg_double_end);
	else
		while (to_parse[j] && !ft_strchr(STOP_F_P, to_parse[j]))
			j++;
	return (j);
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

int	skip_spaces(t_data *data, char *to_parse, int i, int skip)
{
	while (to_parse[i] && to_parse[i] == ' ')
		i++;
	if (skip && to_parse[i] == '$' && char_is_quote(data, to_parse[i + 1]))
		i++;
	return (i);
}