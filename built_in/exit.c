/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 07:24:38 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/30 06:08:30 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_exit()

void	exit_child()

void	exit(t_data *data, t_cmd *cmd, int subshell, int fork)
{
	int	len;

	len = ft_tab_len(cmd -> args);
	if (fork == 0 && len == 1)
		free_all(data, data -> status);
	else if (fork == 0 && len > 1)
		handle_exit();
	else if (fork && len > 1 && !ft_strcmp(cmd -> stop, "|"))
		exit_child();
}
