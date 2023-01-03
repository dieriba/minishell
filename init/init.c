/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 22:43:33 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/03 05:05:13 by dtoure           ###   ########.fr       */
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

void	fill_cmds_par(t_cmd **cmds, char *to_parse, int length)
{
	int		i;
	size_t	j;

	i = -1;
	j = 0;
	j = skip_spaces(to_parse, j, 0);
	while (++i < length)
	{
		set_parenthese(cmds[i], &to_parse[j]);
		j = skip_char_in_str(j, to_parse, STOP_, 1);
		j = skip_char_in_str(j, to_parse, STOP_, 0);
		j = skip_spaces(to_parse, j, 0);
	}
}

int	how_many_cmds(char *to_process)
{
	size_t	i;
	int		count;

	count = 0;
	i = -1;
	while (to_process[++i])
	{
		if (!is_real_stop(to_process, i, STOP_)
			&& to_process[i] == to_process[i + 1])
		{
			++i;
			count++;
		}
		else if (!is_real_stop(to_process, i, STOP_))
			count++;
	}
	count++;
	return (count);
}

void	fill_cmds(t_cmd **cmds, char *to_parse, int length)
{
	int		i;
	size_t	j;

	i = -1;
	j = 0;
	j = skip_spaces(to_parse, j, 0);
	while (++i < length)
	{
		set_redirect_cmd(cmds[i], &to_parse[j], '<');
		set_redirect_cmd(cmds[i], &to_parse[j], '>');
		set_heredoc_app_redirect(cmds[i], &to_parse[j], "<<");
		set_heredoc_app_redirect(cmds[i], &to_parse[j], ">>");
		set_commands(cmds[i], &to_parse[j]);
		set_last_in_last_out(cmds[i]);
		j = skip_char_in_str(j, to_parse, STOP_, 1);
		j = skip_char_in_str(j, to_parse, STOP_, 0);
		j = skip_spaces(to_parse, j, 0);
	}
}

void	init_cmd(t_data *data, char *to_process)
{
	size_t	i;
	size_t	j;

	j = -1;
	data -> cp_to_parse = ft_strdup(to_process);
	is_error(data -> cp_to_parse, MALLOC_ERR, 1);
	quote_to_neg(data -> cp_to_parse);
	i = how_many_cmds(data -> cp_to_parse);
	data -> cmds = ft_calloc(sizeof(t_cmd *), i + 1);
	is_error(data -> cmds, MALLOC_ERR, 1);
	par_to_space(data -> cp_to_parse);
	while (++j < i)
	{
		data -> cmds[j] = ft_calloc(sizeof(t_cmd), 1);
		is_error(data -> cmds, MALLOC_ERR, 1);
		data -> cmds[j]-> data = data;
		data -> cmds[j]-> index = j + 1;
	}
	fill_cmds(data -> cmds, data -> cp_to_parse, i);
	fill_cmds_par(data -> cmds, to_process, i);
	init_path(data -> cmds);
	//print_struct(data -> cmds);
}
