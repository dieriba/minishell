/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 01:59:33 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/02 02:42:42 by dtoure           ###   ########.fr       */
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

static int	skip_to_redirect(char *to_parse, char redirect, size_t i)
{
	while (to_parse[i])
	{
		if (to_parse[i] == redirect && to_parse[i + 1] != redirect
			&& !find_start_quotes(to_parse, i))
		{
			i++;
			i = skip_spaces(to_parse, i, 0);
			if (to_parse[i] == g_data -> neg_single_start
				|| to_parse[i] == g_data -> neg_double_start)
				i++;
			else if (to_parse[i] == '$' 
				&& (to_parse[i + 1] == g_data -> neg_single_start
					|| to_parse[i + 1] == g_data -> neg_double_start))
				i++;
			return (i);
		}
		else if (to_parse[i] == redirect && to_parse[i + 1] == redirect)
			++i;
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
	int		pos;

	k = 0;
	i = -1;
	pos = 0;
	while (to_parse[++i] && is_real_stop(to_parse, i, STOP_))
	{
		if (to_parse[i] == redirect 
			&& to_parse[i + 1] != redirect
			&& !find_start_quotes(to_parse, i))
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

void	set_file_tabs(char **redirection, char *to_parse, char redirect, int length)
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

void	set_redirect_cmd(t_cmd *cmd, char *to_parse, char redirect)
{
	char	**redirection;
	int		length;

	length = find_tab_length(cmd, to_parse, redirect);
	if (length == -1)
		return ;
	redirection = ft_calloc(sizeof(char *), length + 1);
	is_error(redirection, MALLOC_ERR, 1);
	set_file_tabs(redirection, to_parse, redirect, length);
	if (redirect == R_IN)
	{
		cmd -> in = redirection;
		cmd -> in_redirection += length;
	}
	else
	{
		cmd -> out = redirection;
		cmd -> out_redirection += length;
	}
}
