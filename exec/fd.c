/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:28:59 by dtoure            #+#    #+#             */
/*   Updated: 2022/12/31 18:52:53 by dtoure           ###   ########.fr       */
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