/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 03:35:55 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/03 16:34:27 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	new_line(int signal)
{
	if (signal == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_signals(t_data *data)
{
	data -> ctrl_c.sa_handler = new_line;
	data -> ctrl_c.sa_flags = SA_RESTART;
	sigemptyset(&data -> ctrl_c.sa_mask);
	sigaction(SIGINT, &data -> ctrl_c, NULL);
}
