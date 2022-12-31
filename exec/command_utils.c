/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:37:31 by dtoure            #+#    #+#             */
/*   Updated: 2022/12/31 22:13:10 by dtoure           ###   ########.fr       */
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

int	get_status(t_cmd *prev_cmd, pid_t pid_ret, char *stop)
{
	int	status;
	
	if (prev_cmd -> executed)
	{
		if (waitpid(pid_ret, &status, 0) < 0 && errno != ECHILD)
				print_err_and_exit(NULL, "Error with waitpid", 1);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		status = to_exec_or_not(stop, status);
	}
	else
	{
		if (!ft_strcmp("&&", stop))
			status = 1;
		else if (!ft_strcmp("||", stop))
			status = 1;
	}
	return (status);
}

int	prepare_next_step(t_cmd** cmds, char *stop, int i)
{
	int				status;
	static	char	*line;
	
	status = 0;
	if (!line)
		line = stop;
	if (i > 0 && !ft_strcmp("||", line) && cmds[--i]-> pid)
		status = get_status(cmds[i], cmds[i]-> pid, "||");
	else if (i > 0 && !ft_strcmp("&&", line) && cmds[--i]-> pid)
		status = get_status(cmds[i], cmds[i]-> pid, "&&");
	if (!ft_strcmp("|", stop))
	{
		if (pipe(data -> pipes) < 0)
			print_err_and_exit(NULL, PIPE_INIT_ERROR, 0);
		data -> inited = 1;
	}
	line = stop;
	return (status);
}