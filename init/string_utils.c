/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 06:10:50 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/02 06:11:35 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_real_stop(char *to_parse ,size_t i ,char *in)
{
	if (ft_strchr(in ,to_parse[i]) && !find_end_quotes(to_parse, i))
		return (0);
	return (1);
}

int	calcul_word(char *to_parse, char quote, int j)
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

int	skip_spaces(char *to_parse, int i, int skip)
{
	while (to_parse[i] && to_parse[i] == ' ')
		i++;
	if (skip)
	{
		while (to_parse[i] && (to_parse[i] == '"'
				|| to_parse[i] == '\''))
			i++;
	}
	return (i);
}