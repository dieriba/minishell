/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:52:56 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/07 02:41:34 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	where_to_write(t_data *data, t_cmd *cmd)
{
	int		fd;

	fd = 1;
	if (cmd -> last_out && cmd -> last_out -> fd > 0)
		fd = cmd -> last_out -> fd;
	else if (data -> inited && cmd -> p_close == 0)
		fd = data -> pipes[1];
	else if (data -> s_pipes)
		fd = find_write_pipes(data -> s_pipes);
	if (fd < 0)
		return (1);
	return (fd);
}

int	check_line(char *line)
{
	size_t	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '$'
			&& (line[i + 1] == '=' || !line[i]))
			return (1);
		if (line[i] != '_' && !ft_isalpha(line[i]))
			return (1);
	}
	return (0);
}

int	close_redirection(t_cmd *cmd)
{
	if (open_check_files_built_in(cmd, cmd -> tab))
		return (1);
	if (cmd -> last_in && cmd -> last_in -> type == IN)
		close_fd_built_in(&cmd -> last_in -> fd);
	if (cmd -> last_out)
		close_fd_built_in(&cmd -> last_out -> fd);
	return (0);
}

int	dup_and_close_built_in(int fd, int old_fd)
{
	if (dup2(fd, old_fd) < 0)
		return (print_err_built_in("bash", 1));
	return (0);
}

int	set_in_redirection_built_in(t_cmd *cmd)
{
	t_data	*data;
	t_cmd	*prev_cmd;
	int		pipes;
	
	prev_cmd = cmd -> prev_cmd;
	data = cmd -> data;
	pipes = ft_strcmp(prev_cmd -> stop, "|");
	if (cmd -> last_in && cmd -> last_in -> fd > 0)
		return (dup_and_close_built_in(cmd -> last_in -> fd, STDIN_FILENO));
	else if (cmd -> last_in && cmd -> last_in -> fd == 0)
	{
		cmd -> last_in -> fd = find_fd(
				cmd -> data -> here_docs, cmd -> last_in -> files);
		return (dup_and_close_built_in(cmd -> last_in -> fd, STDIN_FILENO));
	}
	else if (pipes == 0 && prev_cmd -> p_close)
		return (dup_and_close_built_in(data -> s_pipes -> read_end -> s_pipes[0], STDIN_FILENO));
	else if (pipes == 0)
		return (dup_and_close_built_in(data -> prev_pipes, STDIN_FILENO));
	return (1);
}