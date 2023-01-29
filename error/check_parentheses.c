/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parentheses.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 14:25:28 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/29 05:40:12 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_next_par(t_data *data, char *to_parse, int *left, int *right)
{
	int		seen;
	size_t	i;

	i = -1;
	seen = 0;
	while (1)
	{
		while (to_parse[++i] && to_parse[i] != ')')
		{
			if (to_parse[i] == '"' || to_parse[i] == '\'')
				i = skip_(to_parse, &i, to_parse[i]);
			if (to_parse[i] == '(')
				(*left) += 1;
			if (to_parse[i] && check_behind_par(to_parse, i))
				return (-1);
			if (ft_strchr(DELIM_TOKEN_SP, to_parse[i])
					&& !find_end_quotes(data, to_parse, i))
				seen = 1;
		}
		if (to_parse[i] == 0 || !find_end_quotes(data, to_parse, i))
			break ;
	}
	while (to_parse[i] && to_parse[i] == ')')
		(*right) += 1;
	if ((*seen == 0) && (*right == 2) && (*left == 2))
		return (-1);
	return (i);
}

int	check_behind_par(char *to_parse, int i)
{
	if (i == 0)
		return (0);
	while (--i > -1 && ft_isspace(to_parse[i]))
		;
	if (!ft_strchr(DELIM_TOKEN_SP, to_parse[i])
		&& to_parse[i] =! '(')
		return (1);
	return (0); 
}

int	valid_num_par(t_data *data, char *to_parse, int right, int left)
{
	int		seen;
	size_t	i;

	i = -1;
	seen = 0;
	while (to_parse[++i] && to_parse[i] == '(')
		left++;
	i+ = find_next_par(data, &to_parse[i], &left, &right);
	if (i == -1)
		return (-1);
	if (left == 2 && right == 2 && seen == 0)
		return (-1);
	if (left > 2 || right > 2)
		return (-1);
	return (i);
}

int	count_parentheses(t_data *data, char *to_parse, char find)
{
	size_t	i;
	int		right;
	
	right = 0;
	i = -1;
	while (to_parse[++i])
	{
		if (to_parse[i] == '"' || to_parse[i] == '\'')
			i += skip_(to_parse, &i, to_parse);
		if (!to_parse[i])
			break ;
		if (to_parse[i] == '(')
			i = valid_num_par(data, &to_parse[i], right)
	}
	return (0);
}

int	valid_parentheses(t_data *data, char *to_parse)
{
	size_t	i;
	int		p_open;
	
	i = -1;
	p_open = 0;
	while (to_parse[++i])
	{
		if (to_parse[i] == '"' || to_parse[i] == '\'')
			i += skip_(to_parse, &i, to_parse[i]);
		if (to_parse[i] == '(' && to_parse[i + 1] == ')')
			return (')');
		else if (to_parse[i] == '(')
			p_open++;
		else if (to_parse [i] == ')')
		{			
			p_open--;
			if (p_open < 0)
				return (')');
		}
		if (to_parse[i] == 0)
			break ;
	}
	if (p_open)
		return (')');
	return (0);
}

int	check_parenthese(t_data *data, char *to_parse)
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
	return (0);
}
