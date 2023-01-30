/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 07:24:38 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/30 17:19:03 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		check_valid_exit(char *num, long long *number)
{
	size_t	len;

	len = ft_strlen(num);
	if (len > 19)
		return (-1);
	(*number) = ft_atoi(num);
	if (*number > __LONG_LONG_MAX__)
		return (-1);
	return (0);
}

void	close_process(t_cmd *cmd, int subshell, int fork, int status)
{
	if (fork == 0)
	{
		handle_pipes(cmd -> data, cmd, subshell);
		free_all(cmd -> data, status);
	}
	else if (cmd)
	{
		close_all(cmd -> data, cmd, subshell);
		free_all(cmd -> data, status);
	}
}


void	handle_exit(t_data *data, t_cmd *cmd, int subshell, int fork)
{
	long long	exit_value;
	int			not_numbered_only;
	int			invalid_exit;
	
	not_numbered_only = ft_numbered_str_only(cmd -> args[1]);
	invalid_exit = check_valid_exit(cmd -> args[1], &exit_value);
	if (!not_numbered_only && !invalid_exit && !cmd -> args[2])
		close_process(cmd, subshell, fork, exit_value % 256);
	else if (!not_numbered_only && !invalid_exit)
	{
		if (ft_putendl_fd("bash : exit: too many arguments", STDERR_FILENO) < 0)
			print_err_and_exit(data, NULL, "syscall", 1);
		data -> status = 1;
		if (fork)
		{
			close_all(data, cmd, subshell);
			free_all(data, data -> status);
		}
	}
	else if (not_numbered_only)
	{
		if (ft_printf("bash : %s: numeric argument required\n", cmd -> args[1]) < 0)
			print_err_and_exit(data, NULL, "syscall", 1);
		close_process(cmd, subshell, fork, STDERR_FILENO);
	}
}

void	exit_process(t_data *data, t_cmd *cmd, int subshell, int fork)
{
	int	len;
	int	curr_stop;
	int	prev_stop;

	curr_stop = ft_strcmp(cmd -> stop, "|");
	prev_stop = ft_strcmp(cmd -> prev_stop, "|");
	len = ft_tab_len(cmd -> args);
	if ((fork == 0 && len == 1) && curr_stop && prev_stop)
		close_process(cmd, subshell, fork, data -> status);
	else if (fork && len == 1)
		close_process(cmd, subshell, fork, data -> status);
	else if ((fork == 0 && len > 1) && curr_stop && prev_stop)
		handle_exit(data, cmd, subshell, fork);
	else if (cmd -> prev_stop && fork && (prev_stop == 0 || curr_stop == 0))
		handle_exit(data, cmd, subshell, fork);
}
