/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 06:18:46 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/31 08:36:55 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd(t_data *data, t_cmd *cmd, int subshell, int fork)
{
	char	*current_dir;
	int		fd;

	if (fork == 0)
		return ;
	fd = where_to_write(data, cmd, subshell);
	current_dir = getcwd(NULL, 0);
	if (current_dir == NULL)
		perror(NULL);
	else if (ft_putendl_fd(current_dir, fd) < 0)
		print_err_and_exit(data, NULL, "syscall", 1);
	ft_free_elem((void **)&current_dir);
}
