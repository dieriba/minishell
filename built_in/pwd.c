/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 06:18:46 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/11 15:05:08 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pwd(t_data *data, t_cmd *cmd)
{
	char	*current_dir;
	int		fd;

	data -> status = 1;
	if (open_check_files_built_in(cmd, cmd -> tab))
		return (1);
	fd = where_to_write(data, cmd);
	current_dir = getcwd(NULL, 0);
	if (current_dir == NULL)
		return (print_err_built_in(cmd, PWD_ERROR GET_CWD_ERR, 1));
	else if (ft_putendl_fd(current_dir, fd) < 0)
		print_err_built_in(cmd, "syscall", 1);
	data -> status = 0;
	ft_free_elem((void **)&current_dir);
	if (cmd && cmd -> last_in && cmd -> last_in -> type == IN)
		close_fd_built_in(&cmd -> last_in -> fd);
	if (cmd && cmd -> last_out)
		close_fd_built_in(&cmd -> last_out -> fd);
	return (1);
}
