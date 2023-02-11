/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:52:36 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/11 16:01:17 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	is_built_in(t_cmd *cmd)
{
	if (cmd == NULL)
		return ;
	else if (ft_strcmp(cmd -> cmd, "/echo") == 0)
		cmd -> built_in = 1;
	else if (ft_strcmp(cmd -> cmd, "/export") == 0)
		cmd -> built_in = 1;
	else if (ft_strcmp(cmd -> cmd, "/unset") == 0)
		cmd -> built_in = 1;
	else if (ft_strcmp(cmd -> cmd, "/env") == 0)
		cmd -> built_in = 1;
	else if (ft_strcmp(cmd -> cmd, "/alias") == 0)
		cmd -> built_in = 1;
	else if (ft_strcmp(cmd -> cmd, "/unalias") == 0)
		cmd -> built_in = 1;
	else if (ft_strcmp(cmd -> cmd, "/pwd") == 0)
		cmd -> built_in = 1;
	else if (ft_strcmp(cmd -> cmd, "/exit") == 0)
		cmd -> built_in = 1;
	else if (ft_strcmp(cmd -> cmd, "/cd") == 0)
		cmd -> built_in = 1;
}

int	built_in(t_data *data, t_cmd *cmd, int fork)
{
	if (cmd -> cmd == NULL)
		return (0);
	if (ft_strcmp(cmd -> cmd, "/echo") == 0)
		return (echo(data, cmd));
	else if (ft_strcmp(cmd -> cmd, "/export") == 0)
		return (export(cmd, data -> env));
	else if (ft_strcmp(cmd -> cmd, "/unset") == 0)
		return (unset(cmd, data -> env));
	else if (ft_strcmp(cmd -> cmd, "/env") == 0)
		return (env(data, cmd));
	else if (ft_strcmp(cmd -> cmd, "/alias") == 0)
		return (alias(data, cmd));
	else if (ft_strcmp(cmd -> cmd, "/unalias") == 0)
		unalias(cmd);
	else if (ft_strcmp(cmd -> cmd, "/pwd") == 0)
		return (pwd(data, cmd));
	else if (ft_strcmp(cmd -> cmd, "/exit") == 0)
		return (exit_process(data, cmd, fork));
	else if (ft_strcmp(cmd -> cmd, "/cd") == 0)
		return (cd(data, cmd));
	return (0);
}
