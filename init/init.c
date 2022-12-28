/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 22:43:33 by dtoure            #+#    #+#             */
/*   Updated: 2022/12/28 21:08:09 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	how_many_cmds(char *to_process)
{
	size_t	i;
	size_t	count;

	i = -1;
	count = 0;
	while (to_process[++i])
	{
		if (ft_strchr(STOP_, to_process[i]))
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
		cmds[0] -> data -> in_redirection = 0;
		cmds[0] -> data -> out_redirection = 0;
		while (to_parse[j] && !ft_strchr(STOP_, to_parse[j]))
			j++;
		j++;
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
		data -> cmds[j] -> data = data;
		data -> cmds[j] -> index = j + 1;
	}
	fill_cmds(data -> cmds, to_process, i);
	print_struct(data -> cmds);
}