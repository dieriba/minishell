/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:52:55 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/14 15:52:53 by dtoure           ###   ########.fr       */
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
	int		i;
	int		length;

	length = 0;
	i = -1;
	while (to_parse[++i])
	{
		i = skip_spaces(data, to_parse, i, 0);
		if (!ft_strchr(FORMAT_TOKEN_SP, to_parse[i]))
		{
			length++;
			while (to_parse[i]
				&& to_parse[i] != ' ' && is_real_stop(data, to_parse, i, STOP_))
				i++;
		}
		if (ft_strchr(R_COMBO, to_parse[i]))
			i = skip_redirect(data, to_parse, i);
		if (i == -1)
			return (length);
		if (!is_real_stop(data, to_parse, i, STOP_) || !to_parse[i])
			break ;
	}
	return (length);
}

void	set_default_data(t_data *data, int len)
{
	int	j;

	j = -1;
	while (++j < len)
	{
		data -> cmds[j] = ft_calloc(sizeof(t_cmd), 1);
		is_error(data, data -> cmds, MALLOC_ERR, 1);
		data -> cmds[j]-> data = data;
		data -> cmds[j]-> index = j + 1;
		data -> cmds[j]-> pos_in = -1;
		data -> cmds[j]-> pos_app = -1;
		data -> cmds[j]-> pos_here = -1;
		data -> cmds[j]-> pos_out = -1;
		if (j > 0)
			data -> cmds[j] -> prev_cmd = data -> cmds[j - 1];
	}
}
