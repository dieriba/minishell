/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 22:43:33 by dtoure            #+#    #+#             */
/*   Updated: 2022/12/30 04:25:28 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_last_in_last_out(t_cmd *cmd)
{
	int	len_in;
	int	len_out;

	len_out = ft_tab_len(cmd -> out) - 1;
	len_in = ft_tab_len(cmd -> in) - 1;
	if (len_in > -1 && cmd -> pos_in >= cmd -> pos_here)
		cmd -> last_in = cmd -> in[len_in];
	if (len_out > -1 && cmd -> pos_out >= cmd -> pos_app)
		cmd -> last_out = cmd -> out[len_out];
}

int	skip_parentheses(char *to_process, size_t i)
{
	int	p_open;

	p_open = 1;
	while (to_process[++i])
	{
		if (to_process[i] == '(')
			p_open++;
		else if (to_process[i] == ')')
			p_open--;
		if (p_open == 0)
		{
			while (to_process[++i] 
				&& !ft_strchr(STOP_, to_process[i]))
				;
			break ;
		}
	}
	return (i);
}

size_t	how_many_cmds(char *to_process)
{
	size_t	i;
	size_t	count;

	i = -1;
	count = 0;
	while (to_process[++i])
	{
		if (to_process[i] == '(')
			i = skip_parentheses(to_process, i);
		if (ft_strchr(STOP_, to_process[i]) 
			&& ft_strchr(STOP_, to_process[i + 1]))
		{
			++i;
			count++;
		}
		else if (ft_strchr(STOP_, to_process[i]))
			count++;
		
	}
	count++;
	return (count);
}

void	fill_cmds(t_cmd **cmds, char *to_parse, int length)
{
	int		i;
	size_t	j;

	j = 0;
	i = -1;
	while (++i < length)
	{
		j = skip_spaces(to_parse, j);
		set_redirect_cmd(cmds[i], &to_parse[j], '<');
		set_redirect_cmd(cmds[i], &to_parse[j], '>');
		set_heredoc_app_redirect(cmds[i], &to_parse[j], "<<");
		set_heredoc_app_redirect(cmds[i], &to_parse[j], ">>");
		set_commands(cmds[i], &to_parse[j]);
		set_last_in_last_out(cmds[i]);
		j = skip_char_in_str(j, to_parse, STOP_, 1);
		j = skip_char_in_str(j, to_parse, STOP_, 0);
		j = skip_spaces(to_parse, j);
	}
}

void	init_cmd(t_data *data, char *to_process)
{
	size_t	i;
	size_t	j;

	j = -1;
	i = how_many_cmds(to_process);
	data -> cmds = ft_calloc(sizeof(t_cmd *), i + 1);
	is_error(data, data -> cmds, MALLOC_ERR);
	while (++j < i)
	{
		data -> cmds[j] = ft_calloc(sizeof(t_cmd), 1);
		is_error(data, data -> cmds, MALLOC_ERR);
		data -> cmds[j]-> data = data;
		data -> cmds[j]-> index = j + 1;
	}
	fill_cmds(data -> cmds, to_process, i);
	print_struct(data -> cmds);
}
