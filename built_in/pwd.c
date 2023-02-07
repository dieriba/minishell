/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 06:18:46 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/07 00:30:27 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pwd(t_data *data, t_cmd *cmd)
{
	char	*current_dir;
	int		fd;

	if (close_redirection(cmd))
		return (print_err_built_in("bash", 1));
	fd = where_to_write(data, cmd);
	current_dir = getcwd(NULL, 0);
	if (current_dir == NULL)
		ft_putstr_fd(PWD_ERROR GET_CWD_ERR, 2);
	else if (ft_putendl_fd(current_dir, fd) < 0)
		print_err_built_in("syscall", 1);
	ft_free_elem((void **)&current_dir);
	return (1);
}
