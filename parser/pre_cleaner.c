/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_cleaner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 02:13:18 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/05 06:01:52 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clean_(char *to_clean, size_t stop)
{
	size_t	i;

	if (ft_strchr(VALID_COMB_EXP, to_clean[1]) || to_clean[1] == 0)
		return ;
	i = -1;
	while (++i < stop)
		to_clean[i] = ' ';
}

void	rid_of_useless_expands(t_data *data, char *to_clean)
{
	size_t	i;
	size_t	j;
	int		flags;

	i = -1;
	while (to_clean[++i])
	{
		j = i;
		flags = 0;
		while (to_clean[i] == '$'
			&& !find_end_quotes(data, to_clean, i)
			&& !char_is_quote(data, to_clean[i + 1]))
		{
			if (is_valid_expand(data, &to_clean[i]))
				flags = 1;
			i += skip_next_stop(data, &to_clean[i]);
		}
		if (flags == 0 && to_clean[j] == '$'
			&& !char_is_quote(data, to_clean[j + 1]))
			clean_(&to_clean[j], i - j);
		if (to_clean[i] == 0)
			break ;
	}
}
