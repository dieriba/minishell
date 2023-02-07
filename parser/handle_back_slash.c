/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_back_slash.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 21:57:27 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/07 00:32:46 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	set_back_to_neg(char *to_clean, size_t i, size_t *len)
{
	while (to_clean[i] && to_clean[i] == '\\')
	{
		if (to_clean[i + 1] == '\\'
			|| to_clean[i - 2] == '\\' * -1)
		{
			*len += 1;
			to_clean[i] = -1 * to_clean[i];
			i += 2;
		}
		else
			i++;
	}
	return (i);
}

size_t	slash_len(t_data *data, char *to_clean, size_t i, size_t *len)
{
	int		quotes;

	quotes = find_end_quotes(data, to_clean, i);
	if (to_clean[i + 1] == 0 || find_single_quote(data, to_clean, i))
		return (i);
	if (to_clean[i + 1] != '\\' && !quotes)
	{
		to_clean[i] = -1 * to_clean[i];
		i++;
	}
	if (to_clean[i + 1] != '\\')
		return (i);
	*len += 1;
	to_clean[i] = -1 * to_clean[i];
	i += (to_clean[i + 1] == '\\') + 1;
	i = set_back_to_neg(to_clean, i, len);
	i -= (to_clean[i] == 0);
	return (i);
}
