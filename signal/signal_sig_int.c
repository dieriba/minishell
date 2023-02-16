/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_sig_int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:04:55 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/17 00:30:00 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sig_int_fork(int signal)
{
	t_cmd	*cmd;
	t_data	*data;

	(void)signal;
	cmd = (t_cmd *)g_collector -> data;
	data = cmd -> data;
	close_all_pipes(data, &data -> here_docs, 1, 1);
	free_all(data, 130);
}
