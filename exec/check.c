/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:28:59 by dtoure            #+#    #+#             */
/*   Updated: 2022/12/31 05:43:24 by dtoure           ###   ########.fr       */
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

void	close_pipes(void)
{
	if (data -> inited == 0)
		return ;
	close_fd("bash", data -> pipes[0]);
	close_fd("bash", data -> pipes[1]);
}