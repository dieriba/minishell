/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 01:59:33 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/23 14:20:05 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

enum e_type file_type(char a, char b)
{
	if (a != b && a == R_IN)
		return (IN);
	else if (a != b && a == R_OUT)
		return (OUT);
	else if (a == b && a == R_IN)
		return (DOC);
	else if (a == b && a == R_OUT)
		return (APPEND);
}

t_files	*copy_files(t_data *data, char *to_parse, int k, int j)
{
	t_files	*redirect;
	int		i;
	int		m;
	
	i = -1;
	m = k;
	while (to_parse[++k] && to_parse[k] == to_parse[k - 1])
		;
	while (to_parse[++k] && (to_parse[k] == ' ' || to_parse[k] == '\t'))
		;	
	redirect = ft_calloc(sizeof(t_files *), 1);
	is_error(data, redirect, MALLOC_ERR, 0);
	redirect -> files = ft_calloc(sizeof(char), (j - k + 1));
	redirect -> type = file_type(to_parse[m], to_parse[m + 1]);
	is_error(data, redirect -> files, MALLOC_ERR, 0);
	while (k < j)
		redirect-> files[++i] = to_parse[k++];
	return (redirect);
}

static int	skip_to_redirect(t_cmd *cmd, char *to_parse, size_t i)
{
	while (to_parse[i])
	{
		if (ft_strchr(R_COMBO, to_parse[i]) && !find_start_quotes(cmd -> data, to_parse, i))
		{
			i++;
			if (to_parse[i] == to_parse[i - 1])
				i++;
			i += skip_spaces(cmd -> data, to_parse, i, 1);
			return (i);
		}
		if (!is_real_stop(cmd -> data, to_parse, i, STOP_))
			return (-1);
		i++;
	}
	return (-1);
}

static int	find_tab_length(t_cmd *cmd, char *to_parse)
{
	size_t	i;
	int		k;

	k = 0;
	i = -1;
	while (to_parse[++i] && is_real_stop(cmd -> data, to_parse, i, STOP_))
	{
		if (ft_strchr(R_COMBO, to_parse[i]) && !find_start_quotes(cmd -> data, to_parse, i))
		{
			k++;
			i += (ft_strchr(R_COMBO, to_parse[i + 1]) > 0);
		}
	}
	if (!k)
		return (-1);
	return (k);
}

void	set_file_tabs(t_cmd *cmd, char *to_parse, int length)
{
	int		i;
	int		j;
	int		k;
	t_files	**redirection;

	i = -1;
	j = 0;
	while (++i < length)
	{
		j = skip_to_redirect(cmd, to_parse, j);
		if (j == -1)
			return ;
		k = j;
		j = find_end_string(cmd -> data, to_parse, j);
		redirection[i] = copy_files(cmd -> data, to_parse, k, j);
	}
}

void	set_redirect_cmd(t_cmd *cmd, char *to_parse)
{
	t_data	*data;
	int		length;

	data = cmd -> data;
	length = find_tab_length(cmd, to_parse);
	if (length == -1)
		return ;
	cmd -> files = ft_calloc(sizeof(t_files *), length + 1);
	is_error(data, cmd -> files, MALLOC_ERR, 0);
	set_file_tabs(cmd, to_parse, length);
}
