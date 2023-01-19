/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 01:59:33 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/19 01:43:55 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	skip_to_redirect(
		t_data *data, char *to_parse, char redirect, size_t i)
{
	while (to_parse[i])
	{
		if (to_parse[i] == redirect && to_parse[i + 1] == redirect
			&& !find_start_quotes(data, to_parse, i))
		{
			i += 2;
			i = skip_spaces(data, to_parse, i, 1);
			return (i);
		}
		if (!is_real_stop(data, to_parse, i, STOP_))
			return (-1);
		i++;
	}
	return (-1);
}

static int	find_tab_length(t_cmd *cmd, char *to_parse, char redirect)
{
	size_t	i;
	int		k;
	int		*pos;

	k = 0;
	i = -1;
	pos = &cmd -> pos_app;
	if (redirect == '<')
		pos = &cmd -> pos_here;
	while (to_parse[++i] && is_real_stop(cmd -> data, to_parse, i, STOP_))
	{
		if ((to_parse[i] == redirect && to_parse[i + 1] == redirect)
			&& !find_start_quotes(cmd -> data, to_parse, i))
		{
			(*pos) = i;
			k++;
		}
	}
	if (to_parse[i] && is_same_token(to_parse[i], to_parse[i + 1]))
		ft_memcpy(cmd-> stop, &to_parse[i], 2);
	cmd -> stop[0] = to_parse[i] - (to_parse[i] == 0);
	k = (k > 0) * k - (k == 0);
	return (k);
}

void	set_tabs_(t_cmd *cmd, char *to_parse, char redirect, int length)
{
	int		i;
	int		j;
	int		k;
	int		m;
	char	**redirection;

	i = -1;
	j = 0;
	redirection = cmd -> out_append;
	if (redirect == R_IN)
		redirection = cmd -> in_here_doc;
	while (++i < length)
	{
		j = skip_to_redirect(cmd -> data, to_parse, redirect, j);
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
	parser(cmd -> data, redirection, 0);
}

void	set_heredoc_app_redirect(t_cmd *cmd, char *to_parse, char *redirect)
{
	int		length;

	length = find_tab_length(cmd, to_parse, redirect[0]);
	if (length == -1)
		return ;
	if (redirect[0] == R_IN)
	{
		cmd -> in_here_doc = ft_calloc(sizeof(char *), length + 1);
		set_tabs_(cmd, to_parse, redirect[0], length);
		is_error(cmd -> data, cmd -> in_here_doc, MALLOC_ERR, 1);
		cmd -> last_in = cmd -> in_here_doc[length - 1];
	}
	else
	{
		cmd -> out_append = ft_calloc(sizeof(char *), length + 1);
		set_tabs_(cmd, to_parse, redirect[0], length);
		is_error(cmd -> data, cmd -> out_append, MALLOC_ERR, 1);
		cmd -> last_out = cmd -> out_append[length - 1];
	}
}
