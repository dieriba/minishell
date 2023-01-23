/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 03:35:55 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/23 01:36:52 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	new_line(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', 0);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	exit_(int signal)
{
	t_data	*data;

	(void)signal;
	data = (t_data *)g_collector -> data;
	close_all_pipes(data, &data -> here_docs, 1, 1);
	free(g_collector);
	exit(130);
}

void	handle_signals()
{
	struct sigaction	ctrl_c;
	
	ctrl_c.sa_flags = 0;
	ctrl_c.sa_handler = new_line;
	sigemptyset(&ctrl_c.sa_mask);
	sigaction(SIGINT, &ctrl_c, NULL);
}
