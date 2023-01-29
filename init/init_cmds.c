/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 02:00:31 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/29 06:47:28 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	move_to_next_word(t_data *data, char *to_parse, int i, int *len)
{
	if (to_parse[i] == '"' * -1 || to_parse[i] == '\'' * -1)
		i = loop_nested_quote (to_parse, i, (to_parse[i] * 2));
	else
		while (to_parse[i] && !ft_isspace(to_parse[i])
			&& is_real_stop(data, to_parse, i, STOP_))
		i++;
	(*len) += 1;
	return (i);
}

int	count_words(t_data *data, char *to_parse)
{
	int		i;
	int		length;

	length = 0;
	i = -1;
	while (to_parse[++i])
	{
		i = skip_spaces(data, to_parse, i, 0);
		if (!ft_strchr(FORMAT_TOKEN_SP, to_parse[i]))
			i = move_to_next_word(data, to_parse, i, &length);
		if (ft_strchr(R_COMBO, to_parse[i]))
			i = skip_redirect(data, to_parse, i);
		if (i == -1)
			return (length);
		if (!is_real_stop(data, to_parse, i, STOP_) || !to_parse[i])
			break ;
	}
	return (length);
}

size_t	skip_redirect(t_data *data, char *to_parse, size_t i)
{
	while (1)
	{
		while (to_parse[i] && ft_strchr(R_COMBO, to_parse[i]))
			i++;
		i = skip_spaces(data, to_parse, i, 0);
		if (to_parse[i] == '"' * -1 || to_parse[i] == '\'' * -1)
			i = loop_nested_quote (to_parse, i, (to_parse[i] * 2));
		else
			while (to_parse[i] && !ft_isspace(to_parse[i]))
				i++;
		i += (to_parse[i] != 0);
		if (!to_parse[i] || !is_real_stop(data, to_parse, i, STOP_))
			return (-1);
		i = skip_spaces(data, to_parse, i, 1);
		if (!ft_strchr(R_COMBO, to_parse[i]))
			break ;
	}
	return (i);
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
		j -= (to_parse[j] == 0);
	}
}

void	set_commands(t_cmd *cmd, char *to_parse)
{
	int	length;

	length = count_words(cmd -> data, to_parse);
	if (length <= 0)
		return ;
	cmd -> args = ft_calloc(sizeof(char *), length + 1);
	is_error(cmd -> data, cmd -> args, MALLOC_ERR, 1);
	set_tabs_cmd(cmd -> data, cmd -> args, to_parse, length);
	cmd -> cmd = cmd -> args[0];
}
