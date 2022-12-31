/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:37:31 by dtoure            #+#    #+#             */
/*   Updated: 2022/12/31 09:31:31 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	open_files(char **files, int length, int flags)
{
	int	i;
	
	i = -1;
	while (++i < length)
	{
		if (open(files[i], flags, 0644) < 0)
			print_err_and_exit(NULL, "bash", 1);
	}
}

void	wait_all_child(t_cmd **cmds)
{
	size_t	i;
	int		status;

	i = -1;
	while (cmds[++i])
	{
		if (waitpid(cmds[i]-> pid, &status, 0) < 0)
			print_err_and_exit(NULL, "Error with waitpid", 1);
	}
	if (WIFEXITED(status))
		data -> status = WEXITSTATUS(status);
}

void	run_cmd(t_cmd *cmd)
{
	size_t	i;

	i = -1;
	if (cmd -> no_path)
	{
		while (cmd -> paths[++i])
		{
			if (access(cmd -> paths[i], X_OK) != -1)
				execve(cmd -> paths[i], cmd -> args, NULL);
		}
		print_err_and_exit(cmd, "bash: ", 1);
	}
	else
	{
		if (access(cmd -> cmd, X_OK) != -1)
			execve(cmd -> cmd, cmd -> args, NULL);
		print_err_and_exit(cmd, "bash: ", 1);
	}
}

int	get_status(pid_t pid_ret)
{
	int	status;

	if (waitpid(pid_ret, &status, 0) < 0)
			print_err_and_exit(NULL, "Error with waitpid", 1);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	return (status);
}

int	prepare_next_step(t_cmd** cmds, char *stop, int i, pid_t pid_ret)
{
	int				status;
	static	char	*line;
	
	status = 0;
	if (!line)
		line = stop; 
	if (i > 0 && !ft_strcmp("||", line) && cmds[--i]-> pid)
		status = get_status(pid_ret);
	else if (i > 0 && !ft_strcmp("&&", line) && cmds[--i]-> pid)
		status = get_status(pid_ret);
	else if (!ft_strcmp("|", stop))
	{
		if (pipe(data -> pipes) < 0)
			print_err_and_exit(NULL, PIPE_INIT_ERROR, 0);
		data -> inited = 1;
	}
	line = stop;
	return (status);
}