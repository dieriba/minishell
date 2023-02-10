/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_back_slash.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 21:57:27 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/10 04:03:37 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	set_back_slash(char *to_clean, size_t i, size_t *len)
{
	while (to_clean[i] && to_clean[i] == '\\')
	{
		if (to_clean[i + 1] == '\\')
		{
			*len += 1;
			if (to_clean[i + 1] == 0)
				break ;
			i += 2;
		}
		else
			i++;
	}
	return (i);
}

size_t	slash_len(char *to_clean, size_t i, size_t *len)
{
	if (to_clean[i + 1] == 0)
		return (i);
	if (to_clean[i + 1] != '\\')
		return (i);
	*len += 1;
	i += 2;
	i = set_back_slash(to_clean, i, len) - 1;
	return (i);
}

size_t	copy_slash(char *to_clean, char *res, size_t *v)
{
	size_t	i;
	size_t	j;
	
	i = (*v);
	j = 0;
	while (to_clean[i] && to_clean[i] == '\\')
	{
		if (to_clean[i + 1] == '\\')
		{
			res[j++] = to_clean[i];
			i += 2;
		}
		else
			i++;
	}
	(*v) = i - 1;
	return (j);
}