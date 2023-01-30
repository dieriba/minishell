/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 02:30:19 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/30 15:21:32 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	dup_(t_data *data, int fd, int old_fd)
{
	if (dup2(fd, old_fd) < 0)
	{
		data -> status = -1;
		print_err_and_exit(data, NULL, "bash78", 1);
	}
}

void	dup_and_close(t_data *data, int fd, int old_fd, int to_close)
{
	if (dup2(fd, old_fd) < 0)
	{
		data -> status = -1;
		print_err_and_exit(data, NULL, "bash5", 1);
	}
	close_fd(data, "bash6", &to_close);
}

void	set_out_redirection(t_cmd *cmd, int subshell)
{
	t_data	*data;

	data = cmd -> data;
	if (cmd -> last_out && cmd -> last_out -> fd > 0)
	{
		//printf("Commande : %s Entered : 1\n", cmd -> cmd);
		dup_(data, cmd -> last_out -> fd, STDOUT_FILENO);
	}
	else if (data -> inited && cmd -> p_close == 0)
	{
		//printf("Commande : %s Entered : 2\n", cmd -> cmd);
		dup_(data, data -> pipes[1], STDOUT_FILENO);
	}
	else if ((cmd -> stop[0] > 0) && subshell && data -> s_pipes_inited)
	{
		//printf("Commande : %s Entered : 3\n", cmd -> cmd);
		dup_(data, data -> p_pipes[1], STDOUT_FILENO);
	}
}

void	set_in_redirection(t_cmd *cmd, int pipes)
{
	t_data	*data;
	t_cmd	*prev_cmd;

	prev_cmd = cmd -> prev_cmd;
	data = cmd -> data;
	if (cmd -> last_in && cmd -> last_in -> fd > 0)
	{
		//printf("Commande : %s Entered : 4\n", cmd -> cmd);
		dup_(data, cmd -> last_in -> fd, STDIN_FILENO);
	}
	else if (cmd -> last_in && cmd -> last_in -> fd == 0)
	{
		//printf("Commande : %s Entered : 5\n", cmd -> cmd);
		cmd -> last_in -> fd = find_fd(
				cmd -> data -> here_docs, cmd -> last_in -> files);
		dup_(data, cmd -> last_in -> fd, STDIN_FILENO);
	}
	else if (prev_cmd && prev_cmd -> p_close && data -> s_pipes_inited)
	{
		//printf("Commande :%s Entered : 6\n", cmd -> cmd);
		dup_(data, data -> p_pipes[0], STDIN_FILENO);
	}
	else if (pipes == 0)
	{
		//printf("Commande :%s Entered : 7\n", cmd -> cmd);
		dup_(data, data -> prev_pipes, STDIN_FILENO);
	}
}

void	set_redirections_files(t_cmd *cmd, char *prev, int subshell)
{
	int	pipes;

	pipes = -1;
	if (prev)
		pipes = ft_strcmp("|", prev);
	open_check_files(cmd, cmd -> tab);
	set_in_redirection(cmd, pipes);
	set_out_redirection(cmd, subshell);
	built_in(cmd -> data, cmd, subshell, 1);
	close_all(cmd -> data, cmd, subshell);
}
