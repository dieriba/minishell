/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 01:59:33 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/03 17:59:31 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_pos(t_cmd *cmd, char redirect, int pos)
{
	if (redirect == '<')
		cmd -> pos_in = pos;
	else
		cmd -> pos_out = pos;
}

static int	skip_to_redirect(
		t_cmd *cmd, char *to_parse, char redirect, size_t i)
{
	while (to_parse[i])
	{
		if (to_parse[i] == redirect && to_parse[i + 1] != redirect
			&& !find_start_quotes(cmd -> data, to_parse, i))
		{
			i++;
			i = skip_spaces(cmd -> data, to_parse, i, 1);
			return (i);
		}
		else if (to_parse[i] == redirect && to_parse[i + 1] == redirect)
			++i;
		if (!is_real_stop(cmd -> data, to_parse, i, STOP_))
			return (-1);
		i++;
	}
	return (-1);
}

static int	find_tab_length(t_cmd *cmd, char *to_parse, char redirect)
{
	size_t	i;
	int		k;
	int		pos;

	k = 0;
	i = -1;
	pos = 0;
	while (to_parse[++i] && is_real_stop(cmd -> data, to_parse, i, STOP_))
	{
		if (to_parse[i] == redirect
			&& to_parse[i + 1] != redirect
			&& !find_start_quotes(cmd -> data, to_parse, i))
		{
			pos = i;
			k++;
		}
		else if (to_parse[i] == redirect && to_parse[i + 1] == redirect)
			++i;
	}
	set_pos(cmd, redirect, pos);
	if (!k)
		return (-1);
	return (k);
}

void	set_file_tabs(t_cmd *cmd, char *to_parse, char redirect, int length)
{
	int		i;
	int		j;
	int		k;
	int		m;
	char	**redirection;

	i = -1;
	j = 0;
	redirection = cmd -> in;
	if (redirect == R_OUT)
		redirection = cmd -> out;
	while (++i < length)
	{
		j = skip_to_redirect(cmd, to_parse, redirect, j);
		if (j == -1)
			return ;
		k = j;
		j = find_end_string(cmd -> data, to_parse, j);
		redirection[i] = ft_calloc(sizeof(char), (j - k + 1));
		is_error(cmd -> data, redirection[i], MALLOC_ERR, 0);
		m = -1;
		while (k < j)
			redirection[i][++m] = to_parse[k++];
	}
}

void	set_redirect_cmd(t_cmd *cmd, char *to_parse, char redirect)
{
	t_data	*data;
	int		length;

	data = cmd -> data;
	length = find_tab_length(cmd, to_parse, redirect);
	if (length == -1)
		return ;
	if (redirect == R_IN)
	{
		cmd -> in = ft_calloc(sizeof(char *), length + 1);
		is_error(data, cmd -> in, MALLOC_ERR, 1);
		set_file_tabs(cmd, to_parse, redirect, length);
		cmd -> in_redirection += length;
	}
	else
	{
		cmd -> out = ft_calloc(sizeof(char *), length + 1);
		is_error(data, cmd -> out, MALLOC_ERR, 1);
		set_file_tabs(cmd, to_parse, redirect, length);
		cmd -> out_redirection += length;
	}
}
