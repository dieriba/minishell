/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 02:30:19 by dtoure            #+#    #+#             */
/*   Updated: 2022/12/31 04:19:48 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	open_infile(t_cmd *cmd)
{
	int	fd;
	
	if (cmd -> last_in && cmd -> pos_in < cmd -> pos_here)
		return (-2);
	else if (cmd -> last_in == NULL)
		return (-1);
	check_files(cmd -> in, F_OK);
	fd = open(cmd -> last_in, O_RDONLY, 0644);
	if (fd == -1)
		print_err_and_exit(NULL, "bash", 1);
	return (fd);
}

int	open_outfile(t_cmd *cmd)
{
	int	fd;
	int	flags;
	int	len_out;
	int	len_out_ap;
	
	if (cmd -> last_out == NULL)
		return (-1);
	len_out = ft_tab_len(cmd -> out);
	len_out_ap = ft_tab_len(cmd -> out_append);
	flags = O_RDWR | O_TRUNC | O_CREAT;
	if (cmd -> out && cmd -> pos_out > cmd -> pos_app)
	{
		if (len_out > 1)
			open_files(cmd -> out, len_out - 1, flags);
		open_files(cmd -> out_append, len_out_ap, O_RDWR | O_APPEND | O_CREAT);
		fd = open(cmd -> out[len_out - 1], flags);
	}
	else
	{
		if (len_out_ap > 1)
			open_files(cmd -> out_append, len_out_ap - 1, flags);
		open_files(cmd -> out, len_out, O_RDWR | O_APPEND | O_CREAT);
		fd = open(cmd -> out_append[len_out_ap - 1], flags);
	}
	if (fd == -1)
		print_err_and_exit(NULL, "bash", 1);
	return (fd);
}

void	set_out_redirection(t_cmd *cmd, int fd)
{
	if (fd > 0)
	{
		if (dup2(fd, STDOUT_FILENO) < 0)
			print_err_and_exit(NULL, "bash", 1);
		if (close(fd) < 0)
			print_err_and_exit(NULL, "bash", 1);
	}
	else if (!ft_strcmp("|", cmd -> stop))
	{
		if (dup2(data -> pipes[1], STDOUT_FILENO) < 0)
			print_err_and_exit(NULL, "bash", 1);
	}
}

void	set_in_redirection(t_cmd *cmd, int fd, int pipes)
{
	if (fd > 0)
	{
		if (dup2(fd, STDIN_FILENO) < 0)
			print_err_and_exit(NULL, "bash", 1);
		if (close(fd) < 0)
			print_err_and_exit(NULL, "bash", 1);
	}
	else if (!pipes)
	{
		if (dup2(data -> prev_pipes, STDOUT_FILENO) < 0)
			print_err_and_exit(NULL, "bash", 1);
	}
}

void	set_redirections_files(t_cmd *cmd, char *str)
{
	int	fd_in;
	int	fd_out;
	int	pipes;
	
	pipes = ft_strcmp("|", str);
	fd_in = open_infile(cmd);
	fd_out = open_outfile(cmd);
	set_in_redirection(cmd, fd_in, pipes);
	set_out_redirection(cmd, fd_out);
	close_pipes();
}