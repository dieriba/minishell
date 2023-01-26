/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 17:27:38 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/26 02:38:22 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	char_is_quote(t_data *data, char c)
{
	if (c == data -> neg_single_start || c == data -> neg_double_start)
		return (1);
	return (0);
}

int	char_is_end_quote(t_data *data, char c)
{
	if (c == data -> neg_single_end || c == data -> neg_double_end)
		return (1);
	return (0);
}

int	find_start_quotes(t_data *data, char *to_parse, int i)
{
	while (--i > -1)
	{
		if (to_parse[i] == data -> neg_single_end
			|| to_parse[i] == data -> neg_double_end)
			break ;
		else if (to_parse[i] == data -> neg_double_start
			|| to_parse[i] == data -> neg_single_start)
			return (1);
	}
	return (0);
}

int	find_end_quotes(t_data *data, char *to_parse, int i)
{
	if (!to_parse[i])
		return (0);
	while (to_parse[++i])
	{
		if (to_parse[i] == data -> neg_single_start
			|| to_parse[i] == data -> neg_double_start)
			break ;
		else if (to_parse[i] == data -> neg_double_end
			|| to_parse[i] == data -> neg_single_end)
			return (1);
	}
	return (0);
}

int	loop_nested_quote(char *to_parse, int j, int end)
{
	while (1)
	{
		while (to_parse[j])
		{
			if (to_parse[j] == end && ft_strchr(STOP_F, to_parse[j + 1]))
				return (j);
			j++;
		}
		if (to_parse[j] == 0)
			break ;
	}
	return (j);
}
