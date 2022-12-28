/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 02:00:31 by dtoure            #+#    #+#             */
/*   Updated: 2022/12/28 08:24:41 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	skip_redirect(char *to_parse, size_t i)
{
	int	flags;

	flags = 1;
	while (1)
	{
		while (to_parse[i] && to_parse[i] == ' ')
			i++;
		if (!to_parse[i] || ft_strchr(STOP_, to_parse[i]))
			return (-1);
		while (to_parse[i] && to_parse[i] != ' ')
			i++;
		if (!to_parse[i] || ft_strchr(STOP_, to_parse[i]))
			return (-1);
		if (!flags && !ft_strchr(R_COMBO, to_parse[i]))
			break ;
		while (to_parse[i] && to_parse[i] == ' ')
			i++;
		if (to_parse[i + 1] && !ft_strchr(R_COMBO, to_parse[i + 1]))
			break ;
		flags = 0;
	}
	return (i);
}

static int	create_tab(char *to_parse)
{
	int		i;
	int		k;

	k = 0;
	i = -1;
	while (to_parse[++i] && !ft_strchr(STOP_, to_parse[i]))
	{
		if (ft_strchr(R_COMBO, to_parse[i]))
			i = skip_redirect(to_parse, i);
		if (i == -1)
			break ;
		while (to_parse[i] && !ft_strchr(STOP, to_parse[i]) && !ft_strchr(R_COMBO, to_parse[i]))
			i++;
		k++;
		if (ft_strchr(STOP_, to_parse[i]) || !to_parse[i])
			break ;
		else if (ft_strchr(R_COMBO, to_parse[i]))
			i--;
	}
	if (!k)
		return (-1);
	return (k);
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
			break ;
		k = j;
		while (to_parse[j] && !ft_strchr(STOP, to_parse[j]) && !ft_strchr(R_COMBO, to_parse[j]))
			j++;
		cmds[i] = ft_calloc(sizeof(char), (j - k + 1));
		//if (!cmds[i])
			//exitfunt
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

	length = create_tab(to_parse);
	if (length == -1)
		return ;
	cmd -> args = ft_calloc(sizeof(char *), length + 1);
	//if (!cmd -> args)
		//exit funct
	set_tabs(cmd -> args, to_parse, length);
	cmd -> cmd = cmd -> args[0];
}