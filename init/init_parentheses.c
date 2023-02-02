/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parentheses.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 01:19:53 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/02 17:16:50 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	par_to_space(t_data *data, char *to_clean)
{
	size_t	i;

	i = -1;
	while (to_clean[++i])
	{
		if ((to_clean[i] == '(' || to_clean[i] == ')')
			&& !find_end_quotes(data, to_clean, i))
			to_clean[i] = ' ';
	}
}

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

int	last_par(t_data *data, char *to_parse)
{
	int	i;
	int	last;

	i = 0;
	last = 0;
	while (to_parse[++i]
		&& is_real_stop(data, to_parse, i, DELIM_TOKEN_SP))
	{
		if (to_parse[i] == ')'
			&& !find_end_quotes(data, to_parse, i))
			last = i;
	}
	i = last;
	if (i == 0)
		return (last);
	while (--i > -1 && (to_parse[i] == ')'
		&& !find_end_quotes(data, to_parse, i)))
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
	while (to_parse[++i] && is_real_stop(cmd -> data, to_parse, i, STOP_))
	{
		if (to_parse[i] == '('
			&& !find_start_quotes(cmd -> data, to_parse, i))
		{
			cmd -> p_open++;
			set_followed_par(cmd, &to_parse[i], &left);
			--left;
		}
		else if (to_parse[i] == ')'
			&& !find_start_quotes(cmd -> data, to_parse, i))
		{
			cmd -> p_close--;
			if (last_par(cmd -> data, &to_parse[i]) < 0)
				set_followed_par(cmd, &to_parse[i], &left);
		}
		cmd -> to_fork = cmd -> p_open;
	}
}
