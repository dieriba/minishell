/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 05:36:27 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/05 05:53:19 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clean_struct(t_data *data)
{
	data -> prev_pipes = -1;
	data -> last_exec_stat = 0;
	data -> inited = 0;
	free_cmd(data -> cmds);
	free(data -> cp_to_parse);
}
