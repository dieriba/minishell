/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:52:55 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/05 06:32:34 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_end_string(t_data *data, char *to_parse, int j)
{
	if (to_parse[j] == data -> neg_single_start)
		j = calcul_word(data, to_parse, j);
	else if (to_parse[j] == data -> neg_double_start)
		j = calcul_word(data, to_parse, j);
	else
		j = calcul_word(data, to_parse, j);
	return (j);
}

int	skip_char_letter_str(t_data *data, size_t i, char *to_parse, char *to_skip)
{
	while (to_parse[i] && is_real_stop(data, to_parse, i, to_skip))
		i++;
	return (i);
}

int	skip_char_token_str(size_t i, char *to_parse, char *to_skip)
{
	while (to_parse[i] && ft_strchr(to_skip, to_parse[i]))
		i++;
	return (i);
}

int	count_words(t_data *data, char *to_parse)
{
	size_t	i;
	int		length;

	i = -1;
	length = 0;
	while (to_parse[++i])
	{
		i = skip_spaces(data, to_parse, i, 0);
		while (to_parse[i] && ft_strchr(R_COMBO, to_parse[i]))
			i++;
		i = skip_spaces(data, to_parse, i, 0);
		while (to_parse[i] && is_real_stop(data, to_parse, i, STOP_F))
			i++;
		length++;
		if (!is_real_stop(data, to_parse, i, STOP_) || !to_parse[i])
			break ;
	}
	if (ft_strchr(STOP_, to_parse[i]) && to_parse[i - 1] == ' ')
		--length;
	return (length);
}

/*int	skip_invalid_dollars(t_data *data, char *to_parse, int j)
{
	while (1)
	{
		if (is_valid_expand(data, &to_parse[j]))
			return (1);
		j += skip_next_stop(&to_parse[j]);
		if (to_parse[j] != '$')
			break ;
		if (to_parse[j] == 0 || !is_real_stop(data, to_parse, j, STOP_))
			return (-1);
	}
	return (j);
}*/