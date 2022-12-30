/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parentheses.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 01:19:53 by dtoure            #+#    #+#             */
/*   Updated: 2022/12/30 01:31:55 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parse_parentheses(char *to_parse)
{
	size_t	i;
	int		p_open;

	p_open =  1;
	i = -1;
	while (to_parse[++i])
	{
		if (to_parse[i] == '(')
			p_open++;
		else if (to_parse[i] == ')')
			p_open--;
		if (p_open == 0)
			break ;
	}
}