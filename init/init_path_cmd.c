/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_path_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:41:48 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/03 16:29:50 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_path(t_cmd *cmds)
{
	char	**tab;

	cmds -> paths = ft_split(cmds -> data -> path + 5, ':');
	is_error(cmds -> data, cmds -> paths, MALLOC_ERR, 0);
	tab = ft_dup_tab(cmds -> paths, cmds -> cmd);
	is_error(cmds -> data, tab, MALLOC_ERR, 0);
	cmds -> paths = tab;
}

void	set_path(t_cmd **cmds)
{
	size_t	i;

	i = -1;
	while (cmds[++i])
	{
		if (cmds[i]-> no_path)
			create_path(cmds[i]);
	}
}

void	set_path_type(t_cmd **cmds)
{
	size_t	i;
	char	*cmd;

	i = -1;
	while (cmds[++i])
	{
		if (cmds[i]-> cmd && !ft_strchr(cmds[i]-> cmd, '/'))
		{
			if (cmds[i]-> cmd)
				cmd = cmds[i]-> cmd;
			cmds[i]-> no_path = 1;
			cmds[i]-> cmd = ft_strjoin("/", cmd);
			is_error(cmds[0]-> data, cmds[i]-> cmd, MALLOC_ERR, 0);
		}
	}		
}

void	init_path(t_cmd **cmds)
{
	set_path_type(cmds);
	set_path(cmds);
}
