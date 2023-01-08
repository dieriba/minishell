/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_path_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:41:48 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/08 22:20:15 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_path(t_cmd *cmd)
{
	char	**tab;

	cmd -> paths = ft_split(cmd -> data -> path + 5, ':');
	is_error(cmd -> data, cmd -> paths, MALLOC_ERR, 0);
	tab = ft_dup_tab(cmd -> paths, cmd -> cmd);
	is_error(cmd -> data, tab, MALLOC_ERR, 0);
	cmd -> paths = tab;
}

void	set_path(t_cmd **cmd)
{
	size_t	i;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i]-> no_path && cmd[i]-> data -> path)
			create_path(cmd[i]);
		else if (cmd[i] -> no_path)
		{
			cmd[i] -> paths = ft_split(cmd[i]-> cmd, '\0');
			is_error(cmd[i] -> data, cmd[i] -> paths, MALLOC_ERR, 0);
		}
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
