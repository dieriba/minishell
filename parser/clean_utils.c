/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 04:25:17 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/04 00:25:17 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*clean_lines(t_data *data, char *line, int expand)
{
	size_t	i;

	i = -1;
	if (line == NULL)
		return (line);
	while (line[++i])
	{
		if (expand && (line[i] == '$' || line[i] == '\\'))
			return (clean_(data, line, 1));
		if (expand == 0 && (line[i] < 0 || line[i] == '\\'))
			return (clean_(data, line, 0));
	}
	return (line);
}
