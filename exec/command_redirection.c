/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 02:30:19 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/24 04:20:46 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	open_infile(t_cmd *cmd)
{
	int	fd;

	fd = -2;
	if (cmd -> last_in == NULL)
		return (-1);
	check_files(cmd -> data, cmd -> tab, F_OK | R_OK);
	if (cmd -> last_in -> type == DOC)
		return (0);
	fd = open(cmd -> last_in -> files, O_RDONLY, 0666);
	if (fd == -1)
		print_err_and_exit(cmd -> data, NULL, "bash", 1);
	return (fd);
}

int	open_outfile(t_cmd *cmd)
{
	int	fd;

	if (cmd -> last_out == NULL)
		return (-1);
	fd = opener_outfile(cmd);
	if (fd == -1)
		print_err_and_exit(cmd -> data, NULL, "bash", 1);
	return (fd);
}

void	set_out_redirection(t_cmd *cmd, int fd, int subshell)
{
	t_data	*data;

	data = cmd -> data;
	if (fd > 0)
	{
		if (dup2(fd, STDOUT_FILENO) < 0)
			print_err_and_exit(data, NULL, "bash", 1);
		close_fd(data, "bash", &fd);
	}
	else if (data -> inited && cmd -> p_close == 0)
	{
		if (dup2(data -> pipes[1], STDOUT_FILENO) < 0)
			print_err_and_exit(data, NULL, "bash", 1);
	}
	else if ((cmd -> stop[0] > 0) && subshell && data -> s_pipes_inited)
	{
		if (dup2(data -> p_pipes[1], STDOUT_FILENO) < 0)
			print_err_and_exit(data, NULL, "bash", 1);
	}
}

void	set_in_redirection(t_cmd *cmd, int fd, int pipes)
{
	t_data	*data;
	t_cmd	*prev_cmd;

	prev_cmd = cmd -> prev_cmd;
	data = cmd -> data;
	if (fd > 0)
	{
		if (dup2(fd, STDIN_FILENO) < 0)
			print_err_and_exit(data, NULL, "bash", 1);
		close_fd(data, "bash", &fd);
	}
	else if (fd == 0)
	{
		fd = find_fd(cmd -> data -> here_docs, cmd -> last_in -> files);
		if (dup2(fd, STDIN_FILENO) < 0)
			print_err_and_exit(cmd -> data, NULL, "bash", 1);
	}
	else if (prev_cmd && prev_cmd -> p_close && data -> s_pipes_inited)
	{
		if (dup2(data -> p_pipes[0], STDIN_FILENO) < 0)
			print_err_and_exit(data, NULL, "bash", 1);
	}
	else if (pipes == 0)
	{
		if (dup2(data -> prev_pipes, STDIN_FILENO) < 0)
			print_err_and_exit(data, NULL, "bash", 1);
	}
}

void	set_redirections_files(t_cmd *cmd, char *prev, int subshell)
{
	int	fd_in;
	int	fd_out;
	int	pipes;

	pipes = -1;
	if (prev)
		pipes = ft_strcmp("|", prev);
	fd_in = open_infile(cmd);
	fd_out = open_outfile(cmd);
	set_in_redirection(cmd, fd_in, pipes);
	set_out_redirection(cmd, fd_out, subshell);
	close_both_pipes(cmd -> data, cmd -> data -> pipes, &cmd -> data -> inited);
	if (subshell == 0 && cmd -> data -> s_pipes_inited)
		close_one_end(cmd -> data, cmd -> data -> p_pipes, 0, &cmd -> data -> s_pipes_inited);
	else if (subshell && cmd -> data -> s_pipes_inited)
		close_one_end(cmd -> data, cmd -> data -> p_pipes, 1, &cmd -> data -> s_pipes_inited);
	close_fd(cmd -> data, "bash", &cmd -> data -> prev_pipes);
	close_all_pipes(cmd -> data, &cmd -> data -> here_docs, 1, 0);
}
