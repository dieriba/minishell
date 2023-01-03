/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 17:31:49 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/03 23:00:31 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	length_(char *to_clean)
{
	size_t	i;
	size_t	len;

	i = 0;
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
	while (to_clean[++i] && !ft_strchr(STOP_EXP, to_clean[i]))
		;
	return (i);
}
