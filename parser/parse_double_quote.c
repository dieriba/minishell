/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_double_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 18:30:25 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/01 19:57:12 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_expand_length(char *to_parse, int *len)
{
	char	stop;
	char	*line;
	size_t	i;

	i = -1;
	while (to_parse[++i])
	{
		if (to_parse[i] == ' ')
			break ;
		else if (to_parse[i] == g_data -> neg_double_end)
			break ;
		else if (to_parse[i] == '"')
			break ;
	}
	stop = to_parse[i];
	to_parse[i] = 0;
	line = get_var_line(find_var(g_data -> env -> start, &to_parse[0]));
	to_parse[i] = stop;
	(*len) += ft_strlen(line);
	return (i);
}

size_t	count_words(char *to_parse)
{
	size_t	len;
	size_t	i;
	char	**tab;
	
	i = -1;
	len = 0;
	while (to_parse[++i] && to_parse[i] != g_data -> neg_double_end)
	{
		if (to_parse[i] == '$')
			i += get_expand_length(&to_parse[++i], &len);
		else if (to_parse[i] == '\\' && to_parse[i++] == '"')
			len++;
		else if (to_parse[i] != '"')
			len++;
		else if (to_parse[i] == '"')
		{
			while (to_parse[++i] != '"')
				len++;
		}
		if (!to_parse[i])
			break ;
	}
	return (len);
}

char	*double_s_q(char *to_parse)
{
	
}