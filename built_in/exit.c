/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 07:24:38 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/11 16:45:28 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_valid_exit(char *num, long long *number)
{
	size_t	len;
	size_t	i;

	i = -1;
	len = 0;
	while (num[++i] && num[i] == '0')
		;
	if (num[i])
		len = ft_strlen(&num[i]);
	if (len > 19)
		return (-1);
	(*number) = ft_atoi(num);
	if (*number > __LONG_LONG_MAX__)
		return (-1);
	return (0);
}

void	close_process(t_cmd *cmd, int fork, int status)
{
	if (fork == 0)
	{
		handle_pipes(cmd -> data, cmd);
		free_all(cmd -> data, status);
	}
	else if (cmd)
	{
		close_all(cmd -> data, cmd);
		free_all(cmd -> data, status);
	}
}

void	print_err_exit_built_in(t_data *data, t_cmd *cmd, char *err, int fork)
{
	if (fork && ft_putendl_fd(err, STDERR_FILENO) < 0)
		print_err_and_exit(data, NULL, "syscall", 1);
	else if (fork == 0)
	{
		if (ft_putendl_fd(err, STDERR_FILENO) < 0)
			print_err_built_in(cmd, "bash", 1);
		return ;
	}
	close_all(data, cmd);
	free_all(data, data -> status);
}

int	handle_exit(t_data *data, t_cmd *cmd, int fork)
{
	long long	exit_value;
	int			not_numbered_only;
	int			invalid_exit;

	data -> status = 1;
	not_numbered_only = ft_numbered_str_only(cmd -> args[1]);
	invalid_exit = check_valid_exit(cmd -> args[1], &exit_value);
	if (!not_numbered_only && !invalid_exit && !cmd -> args[2])
		close_process(cmd, fork, exit_value % 256);
	else if (!not_numbered_only && !invalid_exit)
		print_err_exit_built_in(data, cmd, EXIT_ARGS, fork);
	else if (not_numbered_only)
	{
		data -> status = STDERR_FILENO;
		print_err_exit_built_in(data, cmd, EXIT_NUM_ARGS, fork);
		close_process(cmd, fork, data -> status);
	}
	return (1);
}

int	exit_process(t_data *data, t_cmd *cmd, int fork)
{
	int	len;
	int	curr_stop;
	int	prev_stop;

	curr_stop = ft_strcmp(cmd -> stop, "|");
	prev_stop = ft_strcmp(cmd -> prev_stop, "|");
	len = ft_tab_len(cmd -> args);
	if (fork == 0 && open_check_files_built_in(cmd, cmd -> tab))
		return (1);
	if ((fork == 0 && len == 1) && curr_stop && prev_stop)
		close_process(cmd, fork, data -> status);
	else if (fork && (len == 1 && cmd -> prev_stop))
		close_process(cmd, fork, data -> status);
	else if ((fork == 0 && len > 1) && curr_stop && prev_stop)
		return (handle_exit(data, cmd, fork));
	else if (fork && len > 1)
		handle_exit(data, cmd, fork);
	return (0);
}
