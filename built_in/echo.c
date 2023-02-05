/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 05:38:32 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/05 07:30:54 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	write_to_fd(t_data *data, char *line, int fd)
{
	if (ft_putstr_fd(line, fd) < 0)
	{
		data -> status = 1;
		print_err_and_exit(data, NULL, "syscall", 1);
	}
}

int	echo(t_data *data, t_cmd *cmd)
{
	int	fd;
	int	i;
	int	nl;

	fd = where_to_write(data, cmd);
	if (ft_tab_len(cmd -> args) == 1)
	{
		write_to_fd(data, "\n", fd);
		return (1);
	}
	nl = ft_strcmp(cmd -> args[1], "-n");
	i = (nl == 0) + 1;
	while (cmd -> args[i])
	{
		write_to_fd(data, cmd -> args[i], fd);
		if (cmd -> args[i + 1])
			write_to_fd(data, " ", fd);
		i++;
	}
	if (nl)
		write_to_fd(data, "\n", fd);
	if (cmd -> last_in && cmd -> last_in -> type == IN)
		close_fd(cmd -> data, "bash", &cmd -> last_in -> fd);
	if (cmd -> last_out)
		close_fd(data, "bash", &cmd -> last_out -> fd);
	data -> status = 0;
	return (1);
}
