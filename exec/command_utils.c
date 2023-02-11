/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:37:31 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/11 21:35:25 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	to_exec_or_not(t_cmd *cmd, char *stop, int status, int opt)
{
	if (opt && (cmd -> prev_cmd -> built_in && cmd -> prev_cmd -> executed))
	{	
		data -> last_exec_stat = cmd -> prev_cmd -> exit_status;
		status = cmd -> data -> last_exec_stat;
	}
	if (status == 128 + SIGINT)
		return (-1);
	if (!ft_strcmp("&&", stop) && status == 0)
	{
		cmd -> executed = 1;
		return (0);
	}
	else if (!ft_strcmp("&&", stop))
		return (1);
	else if (!ft_strcmp("||", stop) && status == 0)
		return (1);
	else
	{
		cmd -> executed = 1;
		return (0);
	}
}

void	wait_command_before(t_cmd **cmds, t_cmd *cmd)
{
	int	i;
	int	j;

	i = -1;
	while (cmds[++i])
	{
		if (cmds[i] == cmd)
			break ;
		if (ft_strcmp(cmds[i]-> prev_stop, "|"))
			j = i;
	}
	while (j < i)
	{
		if (waitpid(cmds[j]-> pid, &cmds[j]-> exit_status, 0) < 0
			&& errno != ECHILD)
			print_err_and_exit(cmd -> data, NULL, "Error with waitpid", 1);
		cmds[j]-> waited = 1;
		j++;
	}
}

int	get_status(t_data *data, t_cmd *cmd, pid_t pid_ret, char *stop)
{
	int	status;
	int	pipes;

	status = 0;
	pipes = ft_strcmp("|", stop);
	if (pipes == 0)
		status = pipe_exec(cmd -> prev_cmd);
	else if (pipes)
		wait_command_before(data -> cmds, cmd);
	if (((!status && pid_ret) && pipes))
	{
		if (waitpid(pid_ret, &status, 0) < 0 && errno != ECHILD)
			print_err_and_exit(data, NULL, "Error with waitpid", 1);
		if (WIFEXITED(status))
			data -> status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			data -> status = status;
		data -> last_exec_stat = (data -> status > 0);
		status = to_exec_or_not(cmd, stop, data -> status, 0);
	}
	else if (!status)
		status = to_exec_or_not(cmd, stop, data -> last_exec_stat, 1);
	return (status);
}

void	init_s_pipes(t_data *data, t_cmd **cmds, int i)
{
	t_s_pipes	*node;
	int			p_num;

	p_num = 0;
	node = ft_calloc(sizeof(t_s_pipes), 1);
	is_error(data, node, MALLOC_ERR, 0);
	if (pipe(node -> s_pipes) < 0)
		print_err_and_exit(data, NULL, PIPE_INIT_ERROR, 0);
	while (cmds[i])
	{
		p_num += cmds[i]-> to_fork + cmds[i]-> p_close;
		cmds[i]-> write_end = node;
		if (p_num == 0)
			break ;
		i++;
	}
	cmds[++i]-> read_end = node;
	if (data -> s_pipes == NULL)
		data -> s_pipes = node;
	else
	{
		node -> next = data -> s_pipes;
		data -> s_pipes = node;
	}
}

int	prepare_next_step(t_data *data, t_cmd **cmds, char *stop, int *i)
{
	int			status;

	status = 0;
	if ((*i) > 0 && cmds[(*i) - 1]-> p_close)
	{
		status = get_status(
				data, cmds[(*i)], data -> subshell_pid, cmds[(*i)]-> prev_stop);
	}
	else if ((*i) > 0)
		status = get_status(
				data, cmds[(*i)], cmds[(*i) - 1]-> pid, cmds[(*i)]-> prev_stop);
	if (!status && cmds[(*i)]-> to_fork == 0
		&& cmds[(*i)]-> p_close == 0 && !ft_strcmp("|", stop))
		init_pipes(data, data -> pipes, &data -> inited);
	else if (status == 0 && pipe_par(&cmds[(*i)]) == 0)
		init_s_pipes(data, cmds, (*i));
	if (status > 0 && cmds[(*i)]-> p_open)
		(*i) = end_cmd_par(cmds, *i);
	return (status);
}
