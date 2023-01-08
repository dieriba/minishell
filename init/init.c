/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 22:43:33 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/08 21:11:07 by dtoure           ###   ########.fr       */
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
	t_data	*data;

	data = cmds[0]-> data;
	i = -1;
	j = 0;
	j = skip_spaces(data, to_parse, j, 0);
	while (++i < length)
	{
		set_parenthese(cmds[i], &to_parse[j]);
		j = skip_char_letter_str(cmds[0]-> data, j, to_parse, STOP_);
		j = skip_char_token_str(j, to_parse, STOP_);
		j = skip_spaces(data, to_parse, j, 0);
	}
}

int	how_many_cmds(t_data *data, char *to_process)
{
	size_t	i;
	int		count;

	count = 0;
	i = -1;
	while (to_process[++i])
	{
		if (!is_real_stop(data, to_process, i, STOP_)
			&& to_process[i] == to_process[i + 1])
		{
			++i;
			count++;
		}
		else if (!is_real_stop(data, to_process, i, STOP_))
			count++;
	}
	count++;
	return (count);
}

void	fill_cmds(t_cmd **cmds, char *to_parse, int length)
{
	int		i;
	size_t	j;
	t_data	*data;

	data = cmds[0]-> data;
	i = -1;
	j = skip_spaces(data, to_parse, 0, 0);
	while (++i < length)
	{
		set_redirect_cmd(cmds[i], &to_parse[j], '<');
		set_redirect_cmd(cmds[i], &to_parse[j], '>');
		set_heredoc_app_redirect(cmds[i], &to_parse[j], "<<");
		set_heredoc_app_redirect(cmds[i], &to_parse[j], ">>");
		set_commands(cmds[i], &to_parse[j]);
		set_last_in_last_out(cmds[i]);
		j = skip_char_letter_str(cmds[0]-> data, j, to_parse, STOP_);
		j = skip_char_token_str(j, to_parse, STOP_);
		j = skip_spaces(data, to_parse, j, 0);
	}
}

void	init_cmd(t_data *data, char *to_process)
{
	size_t	len;

	data -> cp_to_parse = ft_strdup(to_process);
	is_error(data, data -> cp_to_parse, MALLOC_ERR, 1);
	quote_to_neg(data, data -> cp_to_parse);
	rid_of_useless_expands(data, data -> cp_to_parse);
	len = how_many_cmds(data, data -> cp_to_parse);
	data -> cmds = ft_calloc(sizeof(t_cmd *), len + 1);
	is_error(data, data -> cmds, MALLOC_ERR, 1);
	par_to_space(data -> cp_to_parse);
	set_default_data(data, len);
	fill_cmds(data -> cmds, data -> cp_to_parse, len);
	fill_cmds_par(data -> cmds, to_process, len);
	init_path(data -> cmds);
	//print_struct(data -> cmds);
}
