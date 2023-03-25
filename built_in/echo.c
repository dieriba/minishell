/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 05:38:32 by dtoure            #+#    #+#             */
/*   Updated: 2023/03/25 22:43:47 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	write_to_fd(t_cmd *cmd, char *line, int fd)
{
	if (ft_putstr_fd(line, fd) < 0)
	{
		cmd -> exit_status = 1;
		return (print_err_built_in(cmd, "syscall", 1));
	}
	return (0);
}

int	no_line_opt(char *to_check)
{
	size_t	i;

	i = 0;
	if (to_check[0] != '-' || to_check[1] == 0)
		return (1);
	while (to_check[++i])
	{
		if (to_check[i] != 'n')
			return (1);
	}
	return (0);
}

void	without_new_line(char **to_check, int *i, int *nl)
{
	int	j;

	(*nl) = no_line_opt(to_check[1]);
	j = 1;
	if (*nl == 0)
	{
		while (to_check[++j])
		{
			if (no_line_opt(to_check[j]))
				break ;
		}
	}
	(*i) = j;
}

int	write_args_(t_cmd *cmd, int fd)
{
	int	i;
	int	nl;

	without_new_line(cmd -> args, &i, &nl);
	while (cmd -> args[i])
	{
		if (write_to_fd(cmd, cmd -> args[i], fd))
			return (-1);
		if (cmd -> args[i + 1])
			if (write_to_fd(cmd, " ", fd))
				return (-1);
		i++;
	}
	if (nl)
		if (write_to_fd(cmd, "\n", fd))
			return (-1);
	return (0);
}

int	echo(t_data *data, t_cmd *cmd)
{
	int	fd;

	cmd -> exit_status = 0;
	if (open_check_files_built_in(cmd, cmd -> tab))
		return (1);
	fd = where_to_write(data, cmd);
	if (ft_tab_len(cmd -> args) == 1)
	{
		if (write_to_fd(cmd, "\n", fd))
			return (1);
	}
	else
		if (write_args_(cmd, fd) < 0)
			return (1);
	if (cmd && cmd -> last_in && cmd -> last_in -> type == IN)
		close_fd_built_in(&cmd -> last_in -> fd);
	if (cmd && cmd -> last_out)
		close_fd_built_in(&cmd -> last_out -> fd);
	return (1);
}
