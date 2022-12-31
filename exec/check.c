/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:28:59 by dtoure            #+#    #+#             */
/*   Updated: 2022/12/31 04:20:24 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_fd(t_data *data, int fd, char *str)
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
	if (close(data -> pipes[0]) < 0 || close(data -> pipes[1]) < 0)
		print_err_and_exit(NULL, "bash", 1); 
}