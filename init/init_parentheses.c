/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parentheses.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 01:19:53 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/05 01:52:51 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	par_to_space(char *to_clean)
{
	size_t	i;

	i = -1;
	while (to_clean[++i])
	{
		if (to_clean[i] == '(' || to_clean[i] == ')')
			to_clean[i] = ' ';
	}
}

void	set_parenthese(t_cmd *cmd, char *to_parse)
{
	size_t	i;

	i = -1;
	while (to_parse[++i] && !ft_strchr(STOP_, to_parse[i]))
	{
		if (to_parse[i] == '(' 
			&& !find_start_quotes(cmd -> data, to_parse, i))
			cmd -> p_open++;
		else if (to_parse[i] == ')'
			&& !find_start_quotes(cmd -> data, to_parse, i))
			cmd -> p_close--;
	}
}
