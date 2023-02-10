/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 03:35:55 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/09 01:23:54 by dtoure           ###   ########.fr       */
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
	free_all(data, 130);
}

void	exit_dumped(int signal)
{
	t_cmd	*cmd;
	t_data	*data;

	(void)signal;
	cmd = (t_cmd *)g_collector -> data;
	data = cmd -> data;
	close_all(data, cmd);
	free_all(data, 131);
}

void	ignore_signals(void)
{
	struct sigaction	ctrl_c;
	
	ctrl_c.sa_handler = SIG_IGN;
	ctrl_c.sa_flags = 0;
	sigemptyset(&ctrl_c.sa_mask);
	sigaction(SIGINT, &ctrl_c, NULL);
}

void	handle_signals(void)
{
	struct sigaction	ctrl_c;
	struct sigaction	sigquit;
	
	ctrl_c.sa_flags = SA_RESTART;
	ctrl_c.sa_handler = new_line;
	sigemptyset(&ctrl_c.sa_mask);
	sigaction(SIGINT, &ctrl_c, NULL);
	sigquit.sa_flags = 0;
	sigquit.sa_handler = SIG_IGN;
	sigemptyset(&sigquit.sa_mask);
	sigaction(SIGQUIT, &sigquit, NULL);
}
