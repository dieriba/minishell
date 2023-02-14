/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 17:27:38 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/14 17:08:12 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	char_is_quote(char c)
{
	if (c == '"' || c == '\'')
		return (1);
	return (0);
}

void	skip_(char *to_parse, size_t *i, int quote)
{
	size_t	j;

	j = (*i);
	while (1)
	{
		while (to_parse[++j])
		{
			if ((to_parse[j] == quote && to_parse[j] == '"')
				&& valid_double(to_parse, j))
				break ;
			else if (to_parse[j] == quote && to_parse[j] != '"')
				break ;
		}
		if (to_parse[j] == 0 || to_parse[j + 1] == 0)
			break ;
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
		while (--j > -1)
		{
			if (to_parse[j] == quote
				&& (to_parse[j] == '\'' || valid_double(to_parse, j)))
				break ;
		}
		if (j >= 0 && (to_parse[j - 1] == '\''
				|| valid_double(to_parse, j - 1)))
			quote = to_parse[--j];
		else
			break ;
	}
	(*i) = j;
}

int	length_word(char *to_parse, size_t j)
{
	while (to_parse[j])
	{
		if ((to_parse[j] == '"' && valid_double(to_parse, j))
			|| to_parse[j] == '\'')
			skip_(to_parse, &j, to_parse[j]);
		if (ft_strchr(STOP_F, to_parse[j]) || ft_isspace(to_parse[j]))
			break ;
		j++;
	}
	return (j);
}
