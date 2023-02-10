/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 02:00:31 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/08 03:24:50 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	move_to_next_word(char *to_parse, size_t i, int *len)
{
	while (to_parse[i])
	{
		if (((to_parse[i] == '"' && valid_double (to_parse, i))) || to_parse[i] == '\'')
			skip_(to_parse, &i, to_parse[i]);
		else if (ft_strchr(STOP_, to_parse[i]) || ft_isspace(to_parse[i]))
			break ;
		i++;
	}
	(*len) += 1;
	if (ft_strchr(STOP_, to_parse[i]) || to_parse[i] == 0)
		return (-1);
	i = skip_spaces(to_parse, i + (to_parse[i] != 0), 0);
	return (i);
}

int	count_words(char *to_parse)
{
	int		i;
	int		length;

	length = 0;
	i = -1;
	while (to_parse[++i])
	{
		i = skip_spaces(to_parse, i, 0);
		if (!ft_strchr(FORMAT_TOKEN_SP, to_parse[i]))
			i = move_to_next_word(to_parse, i, &length) - 1;
		if (i >= 0 && ft_strchr(R_COMBO, to_parse[i]))
			i = skip_redirect(to_parse, i) - 1;
		if (i < 0)
			return (length);
		if (ft_strchr(STOP_, to_parse[i]) || !to_parse[i])
			break ;
	}
	return (length);
}

size_t	skip_redirect(char *to_parse, size_t i)
{
	while (1)
	{
		while (to_parse[i] && ft_strchr(R_COMBO, to_parse[i]))
			i++;
		i = skip_spaces(to_parse, i, 0);
		while (to_parse[i])
		{
			if ((to_parse[i] == '"' && valid_double(to_parse, i)) || to_parse[i] == '\'')
				skip_(to_parse, &i, to_parse[i]);
			else if (ft_strchr(STOP_F, to_parse[i]) || ft_isspace(to_parse[i]))
				break ;
			i++;
		}
		i = skip_spaces(to_parse, i, 1);
		if (!to_parse[i] || ft_strchr(STOP_, to_parse[i]))
			return (-1);
		if (!ft_strchr(R_COMBO, to_parse[i]))
			break ;
	}
	i = skip_spaces(to_parse, i, 1);
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
		if (ft_strchr(R_COMBO, to_parse[++j]))
			j = skip_redirect(to_parse, j);
		if (j == -1 || !to_parse[j])
			return ;
		j = skip_spaces(to_parse, j, 1);
		k = j;
		j = length_word(to_parse, j);
		cmds[i] = ft_calloc(sizeof(char), (j - k + 1));
		is_error(data, cmds[i], MALLOC_ERR, 0);
		m = -1;
		while (k < j)
			cmds[i][++m] = to_parse[k++];
		if (ft_strchr(R_COMBO_DOLLARS, to_parse[j]) || !to_parse[j])
			j--;
	}
}

void	set_commands(t_cmd *cmd, char *to_parse)
{
	int	length;

	length = count_words(to_parse);
	if (length <= 0)
		return ;
	cmd -> args = ft_calloc(sizeof(char *), length + 1);
	is_error(cmd -> data, cmd -> args, MALLOC_ERR, 1);
	set_tabs_cmd(cmd -> data, cmd -> args, to_parse, length);
	cmd -> cmd = cmd -> args[0];
}
