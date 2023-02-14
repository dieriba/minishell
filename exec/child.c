/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 18:52:06 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/11 21:41:32 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_new_line(int *num)
{
	if (*num)
	{
		ft_putchar_fd('\n', 0);
		rl_on_new_line();
		*num = 0;
	}
}

int	loop_through_child(t_data *data, t_cmd **cmds)
{
	int	i;
	int	nl;

	i = -1;
	nl = 1;
	while (cmds[++i])
	{
		if (cmds[i]-> waited)
			data -> status = cmds[i]-> exit_status;
		else if (cmds[i]-> pid && waitpid(
				cmds[i]-> pid, &data -> status, 0) < 0 && errno != ECHILD)
			print_err_and_exit(data, NULL, "Error with waitpid", 1);
		else if (cmds[i]-> built_in && cmds[i]-> executed)
			data -> status = cmds[i]-> exit_status;
		if (cmds[i] && WIFSIGNALED(data -> status)
			&& data -> status == SIGINT && nl)
			print_new_line(&nl);
	}
	if (data -> subshell_pid)
	{
		if (waitpid(data -> subshell_pid,
				&data -> status, 0) < 0 && errno != ECHILD)
			print_err_and_exit(data, NULL, "Error with waitpid", 1);
	}
	return (cmds[--i]-> built_in);
}

void	wait_all_child(t_data *data, t_cmd **cmds)
{
	int	built_in;

	close_all_pipes(data, &data -> here_docs, 1, 0);
	built_in = loop_through_child(data, cmds);
	if (!built_in && WIFEXITED(data -> status))
		data -> status = WEXITSTATUS(data -> status);
	else if (!built_in && WIFSIGNALED(data -> status))
		data -> status = 128 + data -> status;
	handle_signals();
	if (data -> subshell)
		free_all(data, data -> status);
}
