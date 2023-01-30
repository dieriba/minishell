/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 17:31:49 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/30 06:20:01 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	length_(char *to_clean)
{
	size_t	i;
	size_t	len;

	i = -1;
	len = 0;
	while (to_clean[++i])
	{
		if (to_clean[i] > 0)
			len++;
	}
	return (len);
}

char	*cleaner(t_data *data, char *to_clean)
{
	char	*res;
	size_t	i;
	size_t	j;

	i = -1;
	j = -1;
	res = ft_calloc(sizeof(char), length_(to_clean) + 1);
	is_error(data, res, MALLOC_ERR, 0);
	while (to_clean[++i])
		if (to_clean[i] > 0)
			res[++j] = to_clean[i];
	free(to_clean);
	return (res);
}

int	skip_next_stop(char *to_clean)
{
	size_t	i;

	i = -1;
	if (to_clean[0] == '$')
		i = 0;
	while (to_clean[++i])
	{
		if (!ft_isalnum(to_clean[i]) && to_clean[i] != '_'
			&& to_clean[i] != '?')
			break ;
		else if (to_clean[i] < 0)
			break ;
	}
	return (i);
}

size_t	next_quotes(t_data *data, char *to_clean, size_t *len)
{
	size_t	i;

	i = -1;
	while (to_clean[++i] != data -> neg_single_end)
		(*len) += (to_clean[i] > 0);
	return (i);
}
