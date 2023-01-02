/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 01:59:33 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/02 02:48:35 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	skip_to_redirect(char *to_parse, char redirect, size_t i)
{
	while (to_parse[i])
	{
		if (to_parse[i] == redirect && to_parse[i + 1] == redirect
			&& !find_start_quotes(to_parse, i))
		{
			i += 2;
			i = skip_spaces(to_parse, i, 0);
			if (to_parse[i] == g_data -> neg_double_start 
				|| to_parse[i] == g_data -> neg_single_start)
				i++;
			else if (to_parse[i] == '$' 
				&& (to_parse[i + 1] == g_data -> neg_single_start
					|| to_parse[i + 1] == g_data -> neg_double_start))
				i++;
			return (i);
		}
		if (!is_real_stop(to_parse, i, STOP_))
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
	if (redirect == '<')
		pos = &cmd -> pos_here;
	else
		pos = &cmd -> pos_app;
	while (to_parse[++i] && is_real_stop(to_parse, i, STOP_))
	{
		if (to_parse[i] == redirect && to_parse[i + 1] == redirect
			&& !find_start_quotes(to_parse, i))
		{
			(*pos) = i;
			k++;
		}
	}
	if (to_parse[i])
		if (is_same_token(to_parse[i], to_parse[i + 1]))
			ft_memcpy(cmd-> stop, &to_parse[i], 2);
	cmd -> stop[0] = to_parse[i];
	if (!k)
		return (-1);
	return (k);
}

void	set_tabs_(char **redirection, char *to_parse, char redirect, int length)
{
	int	i;
	int	j;
	int	k;
	int	m;

	i = -1;
	j = 0;
	while (++i < length)
	{
		j = skip_to_redirect(to_parse, redirect, j);
		if (j == -1)
			return ;
		k = j;
		if (to_parse[j - 1] == g_data -> neg_single_start)
			j = calcul_word(to_parse, '\'', j);
		else if (to_parse[j - 1] == g_data -> neg_double_start)
			j = calcul_word(to_parse, '"', j);
		else
			j = calcul_word(to_parse, 0, j);
		redirection[i] = ft_calloc(sizeof(char), (j - k + 1));
		is_error(redirection, MALLOC_ERR, 0);
		m = -1;
		while (k < j)
			redirection[i][++m] = to_parse[k++];
	}
}

void	set_heredoc_app_redirect(t_cmd *cmd, char *to_parse, char *redirect)
{
	char	**redirection;
	int		length;

	length = find_tab_length(cmd, to_parse, redirect[0]);
	if (length == -1)
		return ;
	redirection = ft_calloc(sizeof(char *), length + 1);
	is_error(redirection, MALLOC_ERR, 1);
	set_tabs_(redirection, to_parse, redirect[0], length);
	if (redirect[0] == R_IN)
	{
		cmd -> in_here_doc = redirection;
		cmd -> last_in = redirection[length - 1];
		cmd -> in_redirection += length;
	}
	else
	{
		cmd -> out_append = redirection;
		cmd -> last_out = redirection[length - 1];
		cmd -> out_redirection += length;
	}
}
