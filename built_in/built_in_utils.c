/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:52:56 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/11 17:42:13 by dtoure           ###   ########.fr       */
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
	else if (cmd -> write_end && cmd -> write_end -> s_pipes[1] > 0)
		fd = cmd -> write_end -> s_pipes[1];
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
	{	
		cmd -> exit_status = 1;
		return (1);
	}
	if (cmd -> last_in && cmd -> last_in -> type == IN)
		close_fd_built_in(&cmd -> last_in -> fd);
	if (cmd -> last_out)
		close_fd_built_in(&cmd -> last_out -> fd);
	return (0);
}
