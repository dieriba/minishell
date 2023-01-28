/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_index.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 16:25:45 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/28 16:28:28 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_char_index(char *line, char to_find)
{
	size_t	i;

	i = -1;
	while (line[++i] && line[i] != to_find)
		;
	if (line[i])
		return (i);
	return (-1);
}