/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:52:55 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/29 06:49:06 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_end_string(t_data *data, char *to_parse, int j)
{
	if (to_parse[j] == data -> neg_single_start)
		j = loop_nested_quote(to_parse, j, data -> neg_single_end);
	else if (to_parse[j] == data -> neg_double_start)
		j = loop_nested_quote(to_parse, j, data -> neg_double_end);
	else
		while (to_parse[j] && is_real_stop(data, to_parse, j, STOP_F))
			j++;
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

int	add_command(t_data *data, char *to_process, int i)
{
	while (--i >= 0)
	{
		if (!is_real_stop(data, to_process, i, STOP_))
			break ;
		if (is_real_stop(data, to_process, i, STOP_)
			&& !ft_isspace(to_process[i]))
			return (1);
	}
	return (0);
}
