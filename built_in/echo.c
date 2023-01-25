/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 05:38:32 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/25 21:04:13 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	write_to_fd(t_data *data, char *line, int fd)
{
	if (ft_putstr_fd(line, fd) < 0)
		print_err_and_exit(data, NULL, "syscall", 1);
}

void	echo(t_data *data, t_cmd *cmd, int subshell, int fork)
{
	int	fd;
	int	i;
	int	nl;

	if (fork == 0)
		return ;	
	fd = where_to_write(data, cmd, subshell);
	if (ft_tab_len(cmd -> args) == 1)
	{
		write_to_fd(data, "\n", fd);
		return ;
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
}
