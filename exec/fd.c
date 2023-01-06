/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:28:59 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/06 12:45:47 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_fd(t_data *data, char *str, int fd)
{
	if (close(fd) < 0)
		print_err_and_exit(data, NULL, str, 1);
}

void	check_files(t_data *data, char **files, int flags)
{
	int	i;

	i = -1;
	while (files[++i])
	{
		if (access(files[i], flags))
			print_err_and_exit(data, NULL, "bash", 1);
	}
}

void	open_files(t_data *data, char **files, int length, int flags)
{
	int	i;

	i = -1;
	while (++i < length)
	{
		if (open(files[i], flags, 0644) < 0)
			print_err_and_exit(data, NULL, "bash", 1);
	}
}

int	opener_outfile(t_cmd *cmd, int len_out, int len_out_ap)
{
	t_data	*data;
	int		fd;
	int		flags;

	data = cmd -> data;
	flags = O_RDWR | O_TRUNC | O_CREAT;
	if (cmd -> pos_out > cmd -> pos_app)
	{
		if (len_out > 1)
			open_files(data, cmd -> out, len_out - 1, flags);
		open_files(
			data, cmd -> out_append, len_out_ap, flags);
		fd = open(cmd -> out[len_out - 1], flags, 0666);
	}
	else
	{
		flags = O_RDWR | O_APPEND | O_CREAT;
		if (len_out_ap > 1)
			open_files(data, cmd -> out_append, len_out_ap - 1, flags);
		open_files(data, cmd -> out, len_out, flags);
		fd = open(cmd -> out_append[len_out_ap - 1], flags, 0666);
	}
	return (fd);
}
