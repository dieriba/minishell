/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 06:02:28 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/25 14:55:30 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env(t_data *data, t_cmd *cmd, int subshell)
{
	char	**tab;
	size_t	i;

	i = -1;
	tab = data -> env -> tab;
	while (tab[++i])
		ft_putendl_fd(tab[i], where_to_write(data, cmd));
}
