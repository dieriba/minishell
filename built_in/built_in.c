/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:52:36 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/31 08:39:20 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_not_built_in(char *cmd)
{
	if (cmd == NULL)
		return (1);
	else if (ft_strcmp(cmd, "/echo") == 0)
		return (0);
	else if (ft_strcmp(cmd, "/export") == 0)
		return (0);
	else if (ft_strcmp(cmd, "/unset") == 0)
		return (0);
	else if (ft_strcmp(cmd, "/env") == 0)
		return (0);
	else if (ft_strcmp(cmd, "/alias") == 0)
		return (0);
	else if (ft_strcmp(cmd, "/unalias") == 0)
		return (0);
	else if (ft_strcmp(cmd, "/pwd") == 0)
		return (0);
	else if (ft_strcmp(cmd, "/exit") == 0)
		return (0);
	return (1);
}

int	built_in(t_data *data, t_cmd *cmd, int subshell, int fork)
{
	if (cmd -> cmd == NULL)
		return (0);
	if (ft_strcmp(cmd -> cmd, "/echo") == 0)
		echo(data, cmd, subshell, fork);
	else if (ft_strcmp(cmd -> cmd, "/export") == 0)
		export(cmd, data -> env, fork, subshell);
	else if (ft_strcmp(cmd -> cmd, "/unset") == 0)
		unset(cmd, data -> env);
	else if (ft_strcmp(cmd -> cmd, "/env") == 0)
		env(data, cmd, subshell, fork);
	else if (ft_strcmp(cmd -> cmd, "/alias") == 0)
		alias(data, cmd, subshell, fork);
	else if (ft_strcmp(cmd -> cmd, "/unalias") == 0)
		unalias(cmd);
	else if (ft_strcmp(cmd -> cmd, "/pwd") == 0)
		pwd(data, cmd, subshell, fork);
	else if (ft_strcmp(cmd -> cmd, "/exit") == 0)
		return (exit_process(data, cmd, subshell, fork));
	return (0);
}
