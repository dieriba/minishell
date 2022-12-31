/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parentheses.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 01:19:53 by dtoure            #+#    #+#             */
/*   Updated: 2022/12/31 23:12:16 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	par_to_space(char *str)
{
	size_t	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '(' || str[i] == ')')
			str[i] = ' ';
	}
}

void	set_parenthese(t_cmd *cmd, char *to_parse)
{
	size_t	i;

	i = -1;
	while (to_parse[++i] && !ft_strchr(STOP_, to_parse[i]))
	{
		if (to_parse[i] == '(')
			cmd -> p_open++;
		else if (to_parse[i] == ')')
			cmd -> p_close--;
	}
}
