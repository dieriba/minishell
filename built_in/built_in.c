/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:52:36 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/07 02:39:12 by dtoure           ###   ########.fr       */
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
	if (fork == 0 && ft_strcmp(cmd -> cmd, "/echo") == 0)
		return (echo(data, cmd));
	else if (ft_strcmp(cmd -> cmd, "/export") == 0)
		export(cmd, data -> env, fork);
	else if (ft_strcmp(cmd -> cmd, "/unset") == 0)
		unset(cmd, data -> env);
	else if (ft_strcmp(cmd -> cmd, "/env") == 0)
		env(data, cmd, fork);
	else if (ft_strcmp(cmd -> cmd, "/alias") == 0)
		alias(data, cmd, fork);
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
