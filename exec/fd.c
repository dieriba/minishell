/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:28:59 by dtoure            #+#    #+#             */
/*   Updated: 2022/12/31 22:58:54 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_fd(char *str, int fd)
{
	if (close(fd) < 0)
		print_err_and_exit(NULL, str, 1);
}

void	check_files(char **files, int flags)
{
	int	i;

	i = -1;
	while (files[++i])
	{
		if (access(files[i], flags))
			print_err_and_exit(NULL, "bash", 1);
	}
}

void	open_files(char **files, int length, int flags)
{
	int	i;

	i = -1;
	while (++i < length)
	{
		if (open(files[i], flags, 0644) < 0)
			print_err_and_exit(NULL, "bash", 1);
	}
}

int	opener_outfile(t_cmd *cmd, int len_out, int len_out_ap)
{
	int	fd;
	int	flags;

	flags = O_RDWR | O_TRUNC | O_CREAT;
	if (cmd -> pos_out > cmd -> pos_app)
	{
		if (len_out > 1)
			open_files(cmd -> out, len_out - 1, flags);
		open_files(cmd -> out_append, len_out_ap, O_RDWR | O_APPEND | O_CREAT);
		fd = open(cmd -> out[len_out - 1], flags, 0666);
	}
	else
	{
		if (len_out_ap > 1)
			open_files(cmd -> out_append, len_out_ap - 1, flags);
		open_files(cmd -> out, len_out, O_RDWR | O_TRUNC | O_CREAT);
		fd = open(cmd -> out_append[len_out_ap - 1], flags, 0666);
	}
	return (fd);
}
