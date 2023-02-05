/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parentheses.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 01:35:12 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/05 21:10:09 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../includes/minishell.h"

int	end_cmd_par(t_cmd **cmds, size_t i)
{
	int		p_num;

	p_num = 0;
	while (cmds[i])
	{
		p_num += cmds[i]-> p_open + cmds[i]-> p_close;
		if (p_num == 0)
			break ;
		i++;
	}
	return (i);
}

int	pipe_par(t_cmd **cmds)
{
	size_t	i;
	int		p_num;

	p_num = 0;
	i = -1;
	if (cmds[0]-> to_fork == 0)
		return (1);
	while (cmds[++i])
	{
		p_num += cmds[i]-> to_fork + cmds[i]-> p_close;
		if (p_num == 0)
			break ;
	}
	if (cmds[i])
		return (ft_strcmp("|", cmds[i]-> stop));
	return (1);
}
