/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 02:21:14 by dtoure            #+#    #+#             */
/*   Updated: 2022/12/31 02:21:31 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_cmd_in_par(t_cmd **cmds, t_cmd *cmd, int i)
{
	int	p_open;
	int	num;
	
	num = 1;
	if (cmd -> p_open == 0)
		return (0);
	p_open = cmd -> p_open - cmd -> p_close;
	if (p_open == 0)
		return (1);
	while (cmds[++i])
	{
		p_open += cmd -> p_open + cmd -> p_close;
		num++;
		if (p_open == 0)
			break ;
	}
	return (num);
}

char	*find_lim_par(t_cmd **cmds, t_cmd *cmd, int i)
{
	int	p_open;
	
	p_open = cmd -> p_open;
	while (cmds[++i])
	{
		p_open += cmd -> p_open + cmd -> p_close;
		if (p_open == 0)
			return (cmd -> stop) ;
	}
	return (0);
}