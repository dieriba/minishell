/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parentheses.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 01:19:53 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/29 22:38:57 by dtoure           ###   ########.fr       */
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

void	set_followed_par(t_cmd *cmd, char *to_parse, int *flags, size_t i)
{
	printf("Flags value : %d and char : %c\n", *flags, to_parse[i]);
	if (*flags == 2 && to_parse[i] == '(')
	{
		while (to_parse[i++] == '(')
			cmd -> _open++;
		(*flags) -= 1;
	}
	else if (*flags == 1 && to_parse[i] == ')')
	{	
		while (to_parse[i++] == ')')
			cmd -> _close++;
		(*flags) -= 1;
	}
}

int	check_end_par(t_cmd **cmds, int _open)
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
	if (_open == cmds[i]-> _close)
		while (++j < i)
			cmds[i]-> to_not_exec = 1;
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
			i += check_end_par(&cmds[i], cmds[i]-> _open);
	}
}

void	set_parenthese(t_cmd *cmd, char *to_parse)
{
	size_t	i;
	int		flags;
	
	i = -1;
	flags = 2;
	while (to_parse[++i] && is_real_stop(cmd -> data, to_parse, i, STOP_))
	{
		if (to_parse[i] == '('
			&& !find_start_quotes(cmd -> data, to_parse, i))
			cmd -> p_open++;
		else if (to_parse[i] == ')'
			&& !find_start_quotes(cmd -> data, to_parse, i))
			cmd -> p_close--;
		if (to_parse[i] == '(' || to_parse[i] == ')')
			set_followed_par(cmd, to_parse, &flags, i);
		cmd -> to_fork = cmd -> p_open;
	}
}
