/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parentheses.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 14:25:28 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/05 03:50:32 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_parentheses(char *to_parse, char find)
{
	size_t	i;
	int		occur;

	i = -1;
	while (1)
	{
		while (to_parse[++i] && to_parse[i] != find)
			;
		if (!to_parse[i])
			break ;
		occur = 1;
		while (to_parse[++i] && to_parse[i] == find)
			occur++;
		if (occur > 2)
			return (1);
	}
	return (0);
}

int	wrong_format(char *to_parse, size_t i, size_t j)
{
	int	seen;

	seen = 0;
	while (++i < j)
	{
		if (!ft_strchr(FORMAT_TOKEN_SP, to_parse[i]))
			seen = 1;
	}
	if (seen == 0)
		return ('(');
	return (seen);
}

int	check_condition(char *to_parse, size_t i, size_t j)
{
	int	save;

	save = i;
	if (to_parse[i] == '(' && to_parse[i + 1] == ')')
		return (')');
	while (++i < j)
	{
		if (ft_strchr(STOP_, to_parse[i]))
		{
			if (check_behind(to_parse, FORMAT_TOKEN_P, i, save))
				return (')');
			if (to_parse[i] == to_parse[i + 1])
			++i;
		}
		else if (ft_strchr(R_COMBO, to_parse[i]))
		{
			if (wrong_format(to_parse, i, j))
				return (')');
			if (to_parse[i] == to_parse[i + 1])
			++i;
		}
	}
	return (0);
}

int	check_empty_parentheses(char *to_parse)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (1)
	{
		while (to_parse[i] && to_parse[i] != '(' && to_parse[i] != ')')
			i++;
		if (!to_parse[i])
			break ;
		j = i;
		while (to_parse[++i] && to_parse[i] != '(' && to_parse[i] != ')')
			;
		if (check_condition(to_parse, j, i))
			return (')');
	}
	return (0);
}

int	valid_parentheses(char *to_parse)
{
	size_t	i;
	int		p_open;

	i = -1;
	p_open = 0;
	while (to_parse[++i])
	{
		if (to_parse[i] == '(')
			p_open++;
		else if (to_parse [i] == ')')
		{
			p_open--;
			if (p_open < 0)
				return (')');
		}
	}
	if (p_open)
		return (')');
	return (0);
}

int	check_parenthese(char *to_parse)
{
	int	err;

	err = valid_parentheses(to_parse);
	if (err)
		return (err);
	err = count_parentheses(to_parse, '(');
	if (err)
		return (err);
	err = count_parentheses(to_parse, ')');
	if (err)
		return (err);
	err = check_empty_parentheses(to_parse);
	if (err)
		return (err);
	return (0);
}
