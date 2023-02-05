/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 02:30:19 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/05 21:37:41 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	dup_(t_data *data, int fd, int old_fd, int d, char *cmd)
{
	if (dup2(fd, old_fd) < 0)
	{
		printf("Entered is %d %s\n", d, cmd);
		print_err_and_exit(data, NULL, "bash1", 1);
	}
}

void	dup_and_close(t_data *data, int fd, int old_fd, int to_close)
{
	if (dup2(fd, old_fd) < 0)
		print_err_and_exit(data, NULL, "bash", 1);
	close_fd(data, "bash", &to_close);
}

void	set_out_redirection(t_cmd *cmd)
{
	t_data	*data;
	int		fd;
	
	data = cmd -> data;
	fd = 0;
	//printf("Subshdaell %d Command : %s args %s fd value : %d\n", cmd -> data -> subshell, cmd -> args[0], cmd -> args[1], fd);
	fd = find_write_pipes(data -> s_pipes);
	if (cmd -> last_out && cmd -> last_out -> fd > 0)
	{
		//printf("Entered 1\n");
		dup_(data, cmd -> last_out -> fd, STDOUT_FILENO, 1, cmd -> cmd);
	}
	else if (data -> inited && cmd -> p_close == 0)
	{
		//printf("Entered 2\n");
		dup_(data, data -> pipes[1], STDOUT_FILENO, 2, cmd -> cmd);
	}
	else if (fd > 0)
	{
		//printf("Entered 3 Subshell : %d Commande : %s args : %s TO READ : %d\n", cmd -> data -> subshell, cmd -> args[0], cmd -> args[1], fd);
		dup_(data, fd, STDOUT_FILENO, 3, cmd -> cmd);
	}
}

void	set_in_redirection(t_cmd *cmd)
{
	t_data	*data;
	t_cmd	*prev_cmd;
	int		pipes;
	
	prev_cmd = cmd -> prev_cmd;
	data = cmd -> data;
	pipes = ft_strcmp(prev_cmd -> stop, "|");
	if (cmd -> last_in && cmd -> last_in -> fd > 0)
	{
		dup_(data, cmd -> last_in -> fd, STDIN_FILENO, 4, cmd -> cmd);
		//printf("Entered 4\n");
	}
	else if (cmd -> last_in && cmd -> last_in -> fd == 0)
	{
		cmd -> last_in -> fd = find_fd(
				cmd -> data -> here_docs, cmd -> last_in -> files);
		dup_(data, cmd -> last_in -> fd, STDIN_FILENO, 5, cmd -> cmd);
		//printf("Entered 5\n");
	}
	else if (pipes == 0 && prev_cmd -> p_close)
	{
		//printf("Entered 6 Subshell : %d Commande : %s args : %s TO READ : %d\n", cmd -> data -> subshell, cmd -> args[0], cmd -> args[1], data -> s_pipes -> s_pipes[0]);
		dup_(data, data -> s_pipes -> s_pipes[0], STDIN_FILENO, 6, cmd -> cmd);
	}
	else if (pipes == 0)
	{
		//printf("Entered 7\n");
		dup_(data, data -> prev_pipes, STDIN_FILENO, 7, cmd -> cmd);
	}
}	

void	set_redirections_files(t_cmd *cmd)
{
	open_check_files(cmd -> data, cmd, cmd -> tab);
	set_in_redirection(cmd);
	set_out_redirection(cmd);
	built_in(cmd -> data, cmd, 1);
	close_all(cmd -> data, cmd);
}
