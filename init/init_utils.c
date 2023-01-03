/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:52:55 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/03 00:03:51 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_end_string(char *to_parse, int j)
{
	if (to_parse[j] == g_data -> neg_single_start)
		j = calcul_word(to_parse, '\'', j);
	else if (to_parse[j] == g_data -> neg_double_start)
		j = calcul_word(to_parse, '"', j);
	else
		j = calcul_word(to_parse, 0, j);
	return (j);
}

int	skip_char_in_str(size_t i, char *to_parse, char *to_skip, int opt)
{
	if (opt)
		while (to_parse[i] && is_real_stop(to_parse, i, to_skip))
			i++;
	else
		while (to_parse[i] && ft_strchr(to_skip, to_parse[i]))
			i++;
	return (i);
}

int	count_words(char *to_parse)
{
	size_t	i;
	int		length;

	i = -1;
	length = 0;
	while (to_parse[++i])
	{
		while (to_parse[i] && to_parse[i] == ' ')
			i++;
		while (to_parse[i] && ft_strchr(R_COMBO, to_parse[i]))
			i++;
		while (to_parse[i] && to_parse[i] == ' ')
			i++;
		while (to_parse[i] && is_real_stop(to_parse, i, STOP_F))
			i++;
		length++;
		if (!is_real_stop(to_parse, i, STOP_) || !to_parse[i])
			break ;
	}
	if (ft_strchr(STOP_, to_parse[i]) && to_parse[i - 1] == ' ')
		--length;
	return (length);
}
