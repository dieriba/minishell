/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 02:00:31 by dtoure            #+#    #+#             */
/*   Updated: 2022/12/28 22:49:34 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	skip_redirect(char *to_parse, size_t i)
{
	while (1)
	{
		i = skip_spaces(to_parse, i);
		if (!to_parse[i] || ft_strchr(STOP_, to_parse[i]))
			return (-1);
		while (to_parse[i] && to_parse[i] != ' ')
			i++;
		if (!to_parse[i] || ft_strchr(STOP_, to_parse[i]))
			return (-1);
		i = skip_spaces(to_parse, i);
		if (!ft_strchr(R_COMBO, to_parse[i]))
			break ;
	}
	return (i);
}

static void	set_tabs(char **cmds, char *to_parse, int length)
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
		if (j == -1)
			return ;
		j = skip_spaces(to_parse, j);
		k = j;
		while (to_parse[j] && !ft_strchr(STOP_F, to_parse[j]))
			j++;
		cmds[i] = ft_calloc(sizeof(char), (j - k + 1));
		m = -1;
		while (k < j)
			cmds[i][++m] = to_parse[k++];
		if (ft_strchr(R_COMBO, to_parse[j]))
			j--;
	}
}

void	set_commands(t_cmd *cmd, char *to_parse)
{
	int	length;

	length = count_words(to_parse)
		- cmd -> data -> in_redirection - cmd -> data -> out_redirection;
	if (length <= 0)
		return ;
	cmd -> args = ft_calloc(sizeof(char *), length + 1);
	is_error(cmd -> data, cmd -> args, MALLOC_ERR);
	set_tabs(cmd -> args, to_parse, length);
	cmd -> cmd = cmd -> args[0];
}
