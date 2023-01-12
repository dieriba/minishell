/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parentheses.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 01:35:12 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/12 15:15:47 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../includes/minishell.h"

int	find_next_cmd(t_data *data, t_cmd **cmds)
{
	size_t	i;

	i = -1;
	while (cmds[++i] && cmds[i]-> p_close == 0)
		data -> p_num += cmds[i]-> p_open + cmds[i]-> p_close;
	return (i);
}

int	end_cmd_par(t_cmd **cmds, int subshell)
{
	int		p_num;
	size_t	i;

	i = -1;
	p_num = 0;
	while (cmds[++i])
	{
		p_num += cmds[i]-> p_open + cmds[i]-> p_close;
		cmds[0]-> data -> p_num += cmds[i]-> p_open + cmds[i]-> p_close;
		if (subshell == 0 && p_num == 0)
			break ;
		if (subshell == 1 && cmds[i]-> p_close)
			break ;
	}
	return (i);
}