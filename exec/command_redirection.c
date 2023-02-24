/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 02:30:19 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/24 11:33:12 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	dup_(t_data *data, int fd, int old_fd)
{
	if (dup2(fd, old_fd) < 0)
		print_err_and_exit(data, NULL, "minishell1", 1);
}

void	dup_and_close(t_data *data, int fd, int old_fd, int to_close)
{
	if (dup2(fd, old_fd) < 0)
		print_err_and_exit(data, NULL, "minishell", 1);
	close_fd(data, "minishell", &to_close);
}

void	set_out_redirection(t_cmd *cmd)
{
	t_data	*data;

	data = cmd -> data;
	if (cmd -> last_out && cmd -> last_out -> fd > 0)
		dup_(data, cmd -> last_out -> fd, STDOUT_FILENO);
	else if (data -> inited && cmd -> p_close == 0)
		dup_(data, data -> pipes[1], STDOUT_FILENO);
	else if (cmd -> write_end && cmd -> write_end -> s_pipes[1] > 0)
		dup_(data, cmd -> write_end -> s_pipes[1], STDOUT_FILENO);
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
		dup_(data, cmd -> last_in -> fd, STDIN_FILENO);
	else if (cmd -> last_in && cmd -> last_in -> fd == 0)
	{
		cmd -> last_in -> fd = find_fd(
				cmd -> data -> here_docs, cmd -> last_in -> files);
		dup_(data, cmd -> last_in -> fd, STDIN_FILENO);
	}
	else if (pipes == 0 && data -> prev_pipes > 0)
		dup_(data, data -> prev_pipes, STDIN_FILENO);
	else if (cmd -> read_end)
		dup_(data, cmd -> read_end -> s_pipes[0], STDIN_FILENO);
}	

void	set_redirections_files(t_cmd *cmd)
{
	open_check_files(cmd -> data, cmd, cmd -> tab);
	set_in_redirection(cmd);
	set_out_redirection(cmd);
	built_in(cmd -> data, cmd, 1);
	close_all(cmd -> data, cmd);
}
