/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_path_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:41:48 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/31 10:00:30 by dtoure           ###   ########.fr       */
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

void	set_path(t_cmd *cmd)
{
	if (cmd -> no_path && cmd -> data -> path)
		create_path(cmd);
	else if (cmd -> no_path)
	{
		cmd -> paths = ft_split(cmd -> cmd, '\0');
		is_error(cmd -> data, cmd -> paths, MALLOC_ERR, 0);
	}
}

void	set_path_type(t_cmd *cmd)
{
	if (cmd -> cmd && !ft_strchr(cmd -> cmd, '/'))
	{
		cmd -> no_path = 1;
		cmd -> cmd = ft_strjoin("/", cmd -> cmd, 0);
		is_error(cmd -> data, cmd -> cmd, MALLOC_ERR, 0);
	}
}

void	init_path(t_cmd *cmd)
{
	set_path_type(cmd);
	set_path(cmd);
}
