/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 02:00:31 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/04 04:06:57 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		len_invalid_expand(t_data *data, char *to_check)
{
	size_t	i;
	int		len;

	len = 0;
	i = -1;
	while (to_check[++i])
	{
		if (to_check[i] == '$' && !is_valid_expand(data, &to_check[++i]))
			len++;
		if (!is_real_stop(data, to_check, i, STOP_))
			break ;
	}
	return (len);
}

size_t	skip_redirect(t_data *data, char *to_parse, size_t i)
{
	while (1)
	{
		while (to_parse[i] && ft_strchr(R_COMBO, to_parse[i]))
			i++;
		i = skip_spaces(data, to_parse, i, 0);
		while (to_parse[i] && to_parse[i] != ' ')
			i++;
		if (!to_parse[i] || !is_real_stop(data, to_parse, i, STOP_))
			return (-1);
		i = skip_spaces(data, to_parse, i, 1);
		if (!ft_strchr(R_COMBO, to_parse[i]) 
			&& !find_end_quotes(data, to_parse, i))
			break ;
	}
	return (i);
}

int	skip_next_cmd(t_data *data, char *to_parse, size_t j)
{
	if (is_valid_expand(data, &to_parse[j]))
		return (j);
	j += skip_next_stop(&to_parse[j]);
	if (to_parse[j] == 0 || !is_real_stop(data, to_parse, j, STOP_))
		return (-1);
	while (to_parse[++j])
	{
		if (ft_strchr(STOP_, to_parse[j]) && !is_real_stop(data, to_parse, j, STOP_))
			return (-1);
		else if (to_parse[j] == '$' && !find_end_quotes(data, to_parse, j))
		{
			while (1)
			{
				if (is_valid_expand(data, &to_parse[j]) && !find_end_quotes(data, to_parse, j))
					return (j);
				j += skip_next_stop(&to_parse[j]);
				if (to_parse[j] != '$')
					break ;
				if (to_parse[j] == 0 || is_real_stop(data, to_parse, j, STOP_))
					return (-1);
			}
		}
		else if (ft_strchr(R_COMBO, to_parse[j]))
		{
			j = skip_redirect(data, to_parse, j);
			break ;
		}
		else if (!ft_strchr(STOP_F, to_parse[j])
				&& !find_end_quotes(data, to_parse, j))
				break ;
	}
	return (j);
}

void	set_tabs_cmd(t_data *data, char **cmds, char *to_parse, int length)
{
	int		i;
	int		j;
	int		k;
	size_t	m;

	i = -1;
	j = -1;
	while (++i < length)
	{
		if (ft_strchr(R_COMBO, to_parse[++j]) 
			&& !find_start_quotes(data, to_parse, j))
			j = skip_redirect(data, to_parse, j);
		if (to_parse[j] == '$')
			j = skip_next_cmd(data, to_parse, j);
		if (j == -1 || !to_parse[j])
			return ;
		j = skip_spaces(data, to_parse, j, 1);
		k = j;
		j = find_end_string(data, to_parse, j);
		cmds[i] = ft_calloc(sizeof(char), (j - k + 1));
		is_error(data, cmds[i], MALLOC_ERR, 0);
		m = -1;
		while (k < j)
			cmds[i][++m] = to_parse[k++];
		if (ft_strchr(R_COMBO, to_parse[j]) || to_parse[j] == '$')
			j--;
	}
}

void	set_commands(t_cmd *cmd, char *to_parse)
{
	int	length;

	length = count_words(cmd -> data, to_parse) - cmd -> in_redirection
		- cmd -> out_redirection - len_invalid_expand(cmd -> data, to_parse);
	if (length <= 0)
		return ;
	cmd -> args = ft_calloc(sizeof(char *), length + 1);
	is_error(cmd -> data, cmd -> args, MALLOC_ERR, 1);
	set_tabs_cmd(cmd -> data, cmd -> args, to_parse, length);
	parser(cmd -> data, cmd -> args);
	cmd -> cmd = cmd -> args[0];
}
