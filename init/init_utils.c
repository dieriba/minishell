/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:52:55 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/08 02:46:25 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	skip_char_letter_str(char *to_parse, size_t i)
{
	while (to_parse[i])
	{
		if ((to_parse[i] == '"' && valid_double(to_parse, i)) || to_parse[i] == '\'')
			skip_(to_parse, &i, to_parse[i]);
		else if (ft_strchr(STOP_, to_parse[i]))
			break ;
		i++;
	}
	return (i);
}

int	skip_char_token_str(char *to_parse, char *to_skip, size_t i)
{
	while (to_parse[i] && ft_strchr(to_skip, to_parse[i]))
		i++;
	return (i);
}

int	add_command(char *to_process, int i)
{
	while (--i >= 0)
	{
		if (!ft_isspace(to_process[i]))
			break ;
	}
	if (ft_strchr(STOP_, to_process[i]))
		return (0);
	return (1);
}

void	par_to_space(char *to_clean)
{
	size_t	i;

	i = -1;
	while (to_clean[++i])
	{
		if ((to_clean[i] == '"' && valid_double(to_clean, i))
			|| to_clean[i] == '\'')
			skip_(to_clean, &i, to_clean[i]);
		else if ((to_clean[i] == '(' || to_clean[i] == ')'))
			to_clean[i] = ' ';
	}
}
