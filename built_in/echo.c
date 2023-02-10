/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 05:38:32 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/08 03:34:27 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	write_to_fd(t_data *data, char *line, int fd)
{
	if (ft_putstr_fd(line, fd) < 0)
	{
		data -> status = 1;
		return (print_err_built_in("syscall", 1));
	}
	return (0);
}

int	without_new_line(char *to_check)
{
	size_t	i;

	i = 0;
	if (to_check[0] != '-')
		return (1);
	while (to_check[++i])
	{
		if (to_check[i] != 'n')
			return (1);
	}
	return (0);
}

int	write_args_(t_data *data, t_cmd *cmd, int fd)
{
	int	i;
	int	nl;

	nl = without_new_line(cmd -> args[1]);
	i = (nl == 0) + 1;
	while (cmd -> args[i])
	{
		if (write_to_fd(data, cmd -> args[i], fd))
			return (1);
		if (cmd -> args[i + 1])
			if (write_to_fd(data, " ", fd))
				return (1);
		i++;
	}
	if (nl)
		if (write_to_fd(data, "\n", fd) < 0)
			return (1);
	return (0);
}

int	echo(t_data *data, t_cmd *cmd)
{
	int	fd;

	data -> status = 1;
	if (open_check_files_built_in(cmd, cmd -> tab))
		return (1);
	fd = where_to_write(data, cmd);
	if (ft_tab_len(cmd -> args) == 1)
	{
		if (write_to_fd(data, "\n", fd) < 0)
			print_err_built_in("bash", 1);
		return (1);
	}
	write_args_(data, cmd, fd);
	if (cmd -> last_in && cmd -> last_in -> type == IN)
		close_fd_built_in(&cmd -> last_in -> fd);
	if (cmd -> last_out)
		close_fd_built_in(&cmd -> last_out -> fd);
	data -> status = 0;
	return (1);
}
