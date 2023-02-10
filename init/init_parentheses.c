/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parentheses.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 01:19:53 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/10 04:36:42 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_followed_par(t_cmd *cmd, char *to_parse, int *left)
{
	size_t	i;

	i = 0;
	if ((*left) > 0 && to_parse[0] == '(')
		while (to_parse[i++] == '(')
			cmd -> _open++;
	else if (to_parse[0] == ')')
		while (to_parse[i++] == ')')
			cmd -> _close++;
}

int	check_end_par(t_cmd **cmds)
{
	int	i;
	int	j;
	int	p_num;

	p_num = 0;
	i = -1;
	j = -1;
	while (cmds[++i])
	{
		p_num += cmds[i]-> p_close + cmds[i]-> p_open;
		if (p_num == 0)
			break ;
	}
	if (cmds[i] && cmds[i]-> _close > 1)
		while (++j <= i)
			cmds[j]-> to_not_exec = 1;
	return (i);
}

void	real_subshell_or_not(t_cmd **cmds)
{
	int	i;

	i = -1;
	while (cmds[++i])
	{
		if (cmds[i]-> _open > 1
			&& cmds[i]-> _close == cmds[i]-> _open)
			cmds[i]-> to_not_exec = 1;
		else if (cmds[i]-> _open > 1)
			i += check_end_par(&cmds[i]);
		if (cmds[i] == 0)
			break ;
	}
}

int	last_par(char *to_parse)
{
	size_t	i;
	int	last;

	i = 0;
	last = 0;
	while (to_parse[++i])
	{
		if ((to_parse[i] == '"' && valid_double(to_parse, i)) || to_parse[i] == '\'')
			skip_(to_parse, &i, to_parse[i]);
		else if (to_parse[i] == ')')
			last = i;
	}
	i = last;
	if (i == 0)
		return (last);
	while ((int)--i > -1 && (to_parse[i] == ')'))
		;
	last = i;
	return (last);
}

void	set_parenthese(t_cmd *cmd, char *to_parse)
{
	size_t	i;
	int		left;

	left = 1;
	i = -1;
	while (to_parse[++i])
	{
		if ((to_parse[i] == '"' && valid_double(to_parse, i)) || to_parse[i] == '\'')
			skip_(to_parse, &i, to_parse[i]);
		else if (to_parse[i] == '(')
		{
			cmd -> p_open++;
			set_followed_par(cmd, &to_parse[i], &left);
			--left;
		}
		else if (to_parse[i] == ')')
		{
			cmd -> p_close--;
			if (last_par(&to_parse[i]) < 0)
				set_followed_par(cmd, &to_parse[i], &left);
		}
		else if (ft_strchr(STOP_, to_parse[i]))
			break ;
		cmd -> to_fork = cmd -> p_open;
	}
}
