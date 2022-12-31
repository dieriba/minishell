/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 01:59:33 by dtoure            #+#    #+#             */
/*   Updated: 2022/12/30 22:22:16 by dtoure           ###   ########.fr       */
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
		if (to_parse[i] == redirect && to_parse[i + 1] != redirect)
		{
			i++;
			while (to_parse[i] && to_parse[i] == ' ')
				i++;
			return (i);
		}
		else if (to_parse[i] == redirect && to_parse[i + 1] == redirect)
			++i;
		if (ft_strchr(STOP_, to_parse[i]))
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
	while (to_parse[++i] && !ft_strchr(STOP_, to_parse[i]))
	{
		if (to_parse[i] == redirect && to_parse[i + 1] != redirect)
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

int	set_file_tabs(char **redirection, char *to_parse, char redirect, int length)
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
			return (0);
		k = j;
		while (to_parse[j] && !ft_strchr(STOP_F, to_parse[j]))
			j++;
		redirection[i] = ft_calloc(sizeof(char), (j - k + 1));
		if (!redirection[i])
			return (1);
		m = -1;
		while (k < j)
			redirection[i][++m] = to_parse[k++];
	}
	return (0);
}

void	set_redirect_cmd(t_cmd *cmd, char *to_parse, char redirect)
{
	char	**redirection;
	int		length;
	int		err;

	length = find_tab_length(cmd, to_parse, redirect);
	if (length == -1)
		return ;
	redirection = ft_calloc(sizeof(char *), length + 1);
	is_error(redirection, MALLOC_ERR, 1);
	err = set_file_tabs(redirection, to_parse, redirect, length);
	if (err)
		is_error(NULL, MALLOC_ERR, 1);
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
