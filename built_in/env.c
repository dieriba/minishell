/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 06:02:28 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/27 03:44:35 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env(t_data *data, t_cmd *cmd, int subshell, int fork)
{
	char	**tab;
	size_t	i;
	int		fd;

	if (fork == 0)
		return ;
	fd = where_to_write(data, cmd, subshell);
	i = -1;
	tab = data -> env -> tab;
	data -> status = 1;
	while (tab[++i])
	{
		if (ft_putendl_fd(tab[i], fd) < 0)
			print_err_and_exit(data, NULL, "syscall", 1);
	}
	data -> status = 0;
}
