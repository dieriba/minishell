/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 02:30:19 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/14 17:31:07 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	open_infile(t_cmd *cmd)
{
	int	fd;

	fd = -2;
	if (cmd -> last_in == NULL)
		return (-1);
	check_files(cmd -> data, cmd -> in, F_OK | R_OK);
	if (cmd -> pos_here > cmd -> pos_in)
		return (0);
	fd = open(cmd -> last_in, O_RDONLY, 0666);
	if (fd == -1)
		print_err_and_exit(cmd -> data, NULL, "bash", 1);
	return (fd);
}

int	open_outfile(t_cmd *cmd)
{
	int	fd;

	if (cmd -> last_out == NULL)
		return (-1);
	fd = opener_outfile(
			cmd, ft_tab_len(cmd -> out), ft_tab_len(cmd -> out_append));
	if (fd == -1)
		print_err_and_exit(cmd -> data, NULL, "bash", 1);
	return (fd);
}

void	set_out_redirection(t_cmd *cmd, int fd)
{
	if (fd > 0)
	{
		if (dup2(fd, STDOUT_FILENO) < 0)
			print_err_and_exit(cmd -> data, NULL, "bash", 1);
		close_fd(cmd -> data, "bash", fd);
	}
	else if (cmd -> data -> inited && cmd -> p_close == 0)
	{
		if (dup2(cmd -> data -> pipes[1], STDOUT_FILENO) < 0)
			print_err_and_exit(cmd -> data, NULL, "bash", 1);
	}
	else if (cmd -> prev_cmd && cmd -> prev_cmd -> p_close == 0 && cmd -> data -> s_pipes_inited)
	{
		if (dup2(cmd -> data -> p_pipes[1], STDOUT_FILENO) < 0)
			print_err_and_exit(cmd -> data, NULL, "bash", 1);
	}
}

void	set_in_redirection(t_cmd *cmd, int fd, int pipes)
{
	if (fd > 0)
	{
		if (dup2(fd, STDIN_FILENO) < 0)
			print_err_and_exit(cmd -> data, NULL, "bash", 1);
		close_fd(cmd -> data, "bash", fd);
	}
	else if (cmd -> prev_cmd && cmd -> prev_cmd -> p_close)
	{
		if (dup2(cmd -> data -> p_pipes[0], STDIN_FILENO) < 0)
			print_err_and_exit(cmd -> data, NULL, "bash", 1);
	}
	else if (pipes == 0)
	{
		if (dup2(cmd -> data -> prev_pipes, STDIN_FILENO) < 0)
			print_err_and_exit(cmd -> data, NULL, "bash", 1);
	}
}

void	set_redirections_files(t_cmd *cmd, char *prev)
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
	set_out_redirection(cmd, fd_out);
	close_both_pipes(cmd -> data, cmd -> data -> pipes, &cmd -> data -> inited);
	close_both_pipes(cmd -> data, cmd -> data -> p_pipes, &cmd -> data -> s_pipes_inited);
	if (cmd -> data -> prev_pipes > 0)
		close_fd(cmd -> data, "bash", cmd -> data -> prev_pipes);
	cmd -> data -> prev_pipes = -1;
	close_all_pipes(cmd -> data, &cmd -> data -> here_docs, 1, 0);
	cmd -> data -> here_doc_closed = 1;
}
