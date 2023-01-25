/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:52:56 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/25 14:54:40 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int where_to_write(t_data *data, t_cmd *cmd)
{
	int		fd;

	fd = 1;
	if (cmd -> last_out && cmd -> last_out -> fd > 0)
		fd = cmd -> last_out -> fd;
	else if (data -> inited && cmd -> p_close == 0)
		fd = data -> pipes[1];
	else if ((cmd -> stop[0] > 0) && data -> subshell && data -> s_pipes_inited)
		fd = data -> p_pipes[1];
    return (fd);
}