/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 06:02:28 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/25 20:30:42 by dtoure           ###   ########.fr       */
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
	while (tab[++i])
		ft_putendl_fd(tab[i], fd);
}
