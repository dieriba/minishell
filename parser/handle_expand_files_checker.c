/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expand_files_checker.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 19:21:57 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/18 19:25:36 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	skip_and_check_glob(char *to_parse, size_t *i, int quote, char to_find)
{
	size_t	j;

	j = (*i);
	while (1)
	{
		while (to_parse[++j])
		{
			if (to_parse[j] == to_find)
				return (-1);
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
	return (1);
}
