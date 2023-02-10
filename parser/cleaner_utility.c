/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner_utility.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 01:47:46 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/10 05:41:39 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t    copy(char *line, char *res, int quoted)
{
    size_t  i;
    size_t  j;
    char    quote;
    
    j = 0;
    i = -1;
    while (line[++i])
	{
		if ((line[i] == '"' && valid_double(line, i)) || line[i] == '\'')
		{
			quote = line[i];
			while (line[++i] && line[i] != quote)
			{
				if (quoted && ft_isspace(line[i]))
					line[i] = -1 * line[i];
				res[j++] = line[i];
			}
		}
		else
			res[j++] = line[i];
		i -= (line[i] == 0);
	}
    return (j);
}