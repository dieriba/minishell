/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 17:27:38 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/02 00:52:40 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		find_start_quotes(char *to_parse, int i)
{
	while (--i > -1)
	{
		if (to_parse[i] == g_data -> neg_single_end
				|| to_parse[i] == g_data -> neg_double_end)
				break ;
		else if (to_parse[i] == g_data -> neg_double_start
				|| to_parse[i] == g_data -> neg_single_start)
				return (1);
	}
	return (0);
}

int		find_end_quotes(char *to_parse, int i)
{
	printf("The index : %d is real toke,n : %c\n", i, to_parse[i]);
	while (to_parse[++i])
	{
		if (to_parse[i] == g_data -> neg_single_start 
				|| to_parse[i] == g_data -> neg_double_start)
				break ;
		else if (to_parse[i] == g_data -> neg_double_end 
				|| to_parse[i] == g_data -> neg_single_end)
			{
				printf("THis chad is dead %c\n", to_parse[i]);
				return (1);
			}
	}
	return (0);
}

int	length_of_quotes(char *to_parse, char quote)
{
	size_t	i;
	char	end;
	
	i = 0;
	end = g_data -> neg_double_end;
	if (quote == '\'')
		end = g_data -> neg_single_start;
	while (to_parse[++i] && to_parse[i] != end)
		;
	return (i);
}

int		loop_nested_quote(char *to_parse, int j, int end)
{
	while (1)
	{
		while (to_parse[j])
		{
			if (to_parse[j] == end && ft_strchr(STOP_F, to_parse[j + 1]))
				return (j);
			j++;
		}
	}
	return (j);
}