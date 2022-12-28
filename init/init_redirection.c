/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 01:59:33 by dtoure            #+#    #+#             */
/*   Updated: 2022/12/28 18:39:49 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
static int	skip_to_redirect(char *to_parse, char redirect, size_t i)
{
	while (to_parse[++i])
	{
		if  (to_parse[i] == redirect && to_parse[i + 1] == redirect)
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

static void	set_tabs(char **redirection, char *to_parse, char redirect, int length)
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
			return ;
		k = j;
		while (to_parse[j] && (!ft_strchr(STOP, to_parse[j]) && !ft_strchr(R_COMBO, to_parse[j])))
			j++;
		redirection[i] = ft_calloc(sizeof(char), (j - k + 1));
		//if (!redirection[i])
		//	exit error
		m = -1;
		while (k < j)
			redirection[i][++m] = to_parse[k++];
		if (to_parse[j] == redirect)
			j--;
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
	//if (!redirection)
	//	exit function;	
	set_tabs(redirection, to_parse, redirect[0], length);
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