/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:37:31 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/03 17:37:07 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	to_exec_or_not(char *stop, int status)
{	
	if (!ft_strcmp("&&", stop) && status == 0)
		return (0);
	else if (!ft_strcmp("&&", stop))
		return (1);
	else if (!ft_strcmp("||", stop) && status == 0)
		return (1);
	else
		return (0);
}

int	get_status(t_data *data, pid_t pid_ret, char *stop)
{
	int	status;

	status = 0;
	if (pid_ret)
	{
		if (waitpid(pid_ret, &status, 0) < 0 && errno != ECHILD)
			print_err_and_exit(data, NULL, "Error with waitpid", 1);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		data -> last_exec_stat = (status > 0);
		status = to_exec_or_not(stop, status);
	}
	else
		status = to_exec_or_not(stop, data -> last_exec_stat);
	return (status);
}

int	prepare_next_step(t_cmd **cmds, char *stop, int i)
{
	int			status;
	static char	*line;
	t_data		*data;

	data = cmds[0]-> data;
	status = 0;
	if (!line)
		line = stop;
	if (i > 0 && !ft_strcmp("||", line))
		status = get_status(data, cmds[i - 1]-> pid, "||");
	else if (i > 0 && !ft_strcmp("&&", line))
		status = get_status(data, cmds[i - 1]-> pid, "&&");
	if (!ft_strcmp("|", stop))
	{
		if (pipe(data -> pipes) < 0)
			print_err_and_exit(data, NULL, PIPE_INIT_ERROR, 0);
		data -> inited = 1;
	}
	line = stop;
	return (status);
}
