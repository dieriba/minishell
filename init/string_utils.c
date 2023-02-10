/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 06:10:50 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/08 02:52:29 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_same_token(char c, char d)
{
	if (ft_strchr(FORMAT_TOKEN, c) && ft_strchr(FORMAT_TOKEN, d))
	{
		if (c == d)
			return (1);
	}
	return (0);
}

int	skip_spaces(char *to_parse, int i, int skip)
{
	while (to_parse[i] && ft_isspace(to_parse[i]))
		i++;
	if (skip && (to_parse[i] == '$' && char_is_quote(to_parse[i + 1])))
		i++;
	return (i);
}
