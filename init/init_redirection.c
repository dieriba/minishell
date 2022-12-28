/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 01:59:33 by dtoure            #+#    #+#             */
/*   Updated: 2022/12/28 22:48:39 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	skip_to_redirect(char *to_parse, char redirect, size_t i)
{
	while (to_parse[++i])
	{
		if (to_parse[i] == redirect && to_parse[i + 1] == redirect)
		{
			i += 2;
			while (to_parse[i] && to_parse[i] == ' ')
				i++;
			return (i);
		}
		if (ft_strchr(STOP_, to_parse[i]))
			return (-1);
	}
	return (-1);
}

static int	find_tab_length(t_cmd *cmd, char *to_parse, char redirect)
{
	size_t	i;
	int		k;

	k = 0;
	i = -1;
	while (to_parse[++i] && !ft_strchr(STOP_, to_parse[i]))
	{
		if (to_parse[i] == redirect && to_parse[i + 1] == redirect)
			k++;
	}
	if (ft_strchr(STOP_, to_parse[i]))
		cmd -> stop = to_parse[i];
	if (!k)
		return (-1);
	return (k);
}

int	set_tabs_(char **redirection, char *to_parse, char redirect, int length)
{
	int	i;
	int	j;
	int	k;
	int	m;

	i = -1;
	j = -1;
	while (++i < length)
	{
		j = skip_to_redirect(to_parse, redirect, j);
		if (j == -1)
			return (0);
		k = j;
		while (to_parse[j] && (!ft_strchr(STOP_F, to_parse[j])))
			j++;
		redirection[i] = ft_calloc(sizeof(char), (j - k + 1));
		if (!redirection[i])
			return (1);
		m = -1;
		while (k < j)
			redirection[i][++m] = to_parse[k++];
		if (to_parse[j] == redirect)
			j--;
	}
	return (0);
}

void	set_heredoc_app_redirect(t_cmd *cmd, char *to_parse, char *redirect)
{
	char	**redirection;
	int		length;
	int		err;

	length = find_tab_length(cmd, to_parse, redirect[0]);
	if (length == -1)
		return ;
	redirection = ft_calloc(sizeof(char *), length + 1);
	is_error(cmd -> data, redirection, MALLOC_ERR);
	err = set_tabs_(redirection, to_parse, redirect[0], length);
	if (err)
		is_error(cmd -> data, NULL, MALLOC_ERR);
	if (redirect[0] == R_IN)
	{
		cmd -> in_here_doc = redirection;
		cmd -> data -> in_redirection += length;
	}
	else
	{
		cmd -> out_append = redirection;
		cmd -> data -> out_redirection += length;
	}
}