/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 13:57:51 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/29 02:48:48 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_quotes(char *to_parse, int i)
{
	while (--i > -1)
	{
		if (to_parse[i] == '"' || to_parse[i] == '\'')
			return (1);
	}
	return (0);
}

int	how_many_quotes(char *to_parse, char quote, int *count)
{
	size_t	i;

	i = 0;
	while (to_parse[++i])
	{
		if (to_parse[i] == '"' && to_parse[i - 1] != '\\')
			break ;
		else if (to_parse[i] == quote && quote == '\'')
			break ;
	}
	(*count) += 1 + (to_parse[i] == quote);
	return (i);
}

int	valid_quotes(t_data *data, char *to_parse)
{
	size_t	i;
	int		sing_q;
	int		double_q;
	
	i = -1;
	sing_q = 0;
	double_q = 0;
	while (to_parse[++i])
	{
		if (to_parse[i] == '"')
			i += how_many_quotes(&to_parse[i], '"', &double_q);
		else if (to_parse[i] == '\'')
			i += how_many_quotes(&to_parse[i], '\'', &sing_q);
		if (to_parse[i] == 0)
			break ;
	}
	if (sing_q % 2 || double_q % 2)
	{
		print_bad_syntax(data, MISSING_QUOTES, 0);
		return (1);
	}
	return (0);
}

void	quote_to_neg(t_data *data, char *to_parse)
{
	size_t	i;

	i = -1;
	while (to_parse[++i])
	{
		if (to_parse[i] && to_parse[i] == '"')
		{
			to_parse[i] = data -> neg_double_start;
			while (to_parse[++i])
				if (to_parse[i] == '"' && to_parse[i - 1] != '\\')
					break ;
			if (to_parse[i])
				to_parse[i] = data -> neg_double_end;
		}
		else if (to_parse[i] && to_parse[i] == '\'')
		{
			to_parse[i] = data -> neg_single_start;
			while (to_parse[++i] && to_parse[i] != '\'')
				;
			if (to_parse[i])
				to_parse[i] = data -> neg_single_end;
		}
		if (!to_parse[i])
			break ;
	}
}
