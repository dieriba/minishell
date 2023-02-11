/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 06:02:28 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/11 16:44:12 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	env(t_data *data, t_cmd *cmd)
{
	char	**tab;
	size_t	i;
	int		fd;

	data -> status = 0;
	if (open_check_files_built_in(cmd, cmd -> tab))
		return (1);
	fd = where_to_write(data, cmd);
	i = -1;
	tab = data -> env -> tab;
	while (tab[++i])
	{
		if (ft_putendl_fd(tab[i], fd) < 0)
		{
			data -> status = 1;
			return (print_err_built_in(cmd, "bash", 1));
		}
	}
	if (cmd && cmd -> last_in && cmd -> last_in -> type == IN)
		close_fd_built_in(&cmd -> last_in -> fd);
	if (cmd && cmd -> last_out)
		close_fd_built_in(&cmd -> last_out -> fd);
	return (1);
}
