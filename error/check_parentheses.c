/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parentheses.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 14:25:28 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/24 11:18:39 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	valid_empty_par(char *to_parse, int i, int j)
{
	if (i > 0 && to_parse[--i] != '(' && to_parse[--j] != ')')
		return (1);
	else if (i == 0)
		return (1);
	return (0);
}

int	check_right_par(char *to_parse, int i, int j)
{
	if ((ft_strchr(DELIM_TOKEN_SP, to_parse[i])
			&& to_parse[i] != ';'))
		return (1);
	else if (to_parse[i] == '(' && valid_empty_par(to_parse, i, j))
		return (1);
	else if (to_parse[i] != ';' && to_parse[i] != ')')
	{
		while (i > -1)
		{
			if (to_parse[i] == '"' || to_parse[i] == '\'')
				skip_reverse(to_parse, &i, to_parse[i]);
			if (to_parse[i] == ')')
				return (1);
			else if (ft_strchr(DELIM_TOKEN_SP, to_parse[i])
				|| to_parse[i] == '(')
				break ;
			i--;
		}
	}
	return (0);
}

int	check_behind_par(char *to_parse, int i)
{
	int	j;

	j = i;
	while (--i > -1 && ft_isspace(to_parse[i]))
		;
	if ((i >= 0 && to_parse[j] == '(')
		&& (!ft_strchr(DELIM_TOKEN_SP, to_parse[i])
			&& to_parse[i] != '('))
		return (')');
	else if (to_parse[j] == ')')
		return (check_right_par(to_parse, i, j));
	return (0);
}

int	valid_parentheses(char *to_parse, int *_open, size_t i)
{
	if (to_parse[i] == '(')
		(*_open) += 1;
	else if (to_parse[i] == ')')
	{			
		(*_open) -= 1;
		if ((*_open) < 0)
			return (-1);
	}
	return (*_open);
}
