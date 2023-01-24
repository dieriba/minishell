/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 17:24:51 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/24 03:16:22 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	print_bad_syntax(t_data *data, char *str, char token)
{
	ft_putstr_fd(str, 2);
	ft_putchar_fd(token, 2);
	ft_putchar_fd('\n', 2);
	data -> status = 2;
	return (1);
}

void	print_err(t_data *data, char *str, t_cmd *cmd, int type)
{
	if (errno == 2 && cmd && cmd -> no_path)
	{
		ft_putstr_fd("bash: command not found: ", 2);
		ft_putstr_fd(cmd -> args[0], 2);
		ft_putchar_fd('\n', 2);
		data -> status = 127;
	}
	else if (errno == 2 && cmd && !cmd -> no_path)
	{
		ft_putstr_fd("bash: no such file or directory: ", 2);
		ft_putstr_fd(cmd -> cmd, 2);
		ft_putchar_fd('\n', 2);
		data -> status = 127;
	}
	else if (type)
		perror(str);
	else
	{
		ft_putstr_fd(str, 2);
		ft_putchar_fd('\n', 2);
	}
}

void	print_err_and_exit(t_data *data, t_cmd *cmd, char *err_msg, int type)
{
	if (data -> subshell == 0 && data -> s_pipes_inited)
		close_one_end(data, data -> p_pipes, 0, &data -> s_pipes_inited);
	else if (data -> subshell && data -> s_pipes_inited)
		close_one_end(data, data -> p_pipes, 1, &data -> s_pipes_inited);
	close_both_pipes(data, data -> pipes, &data -> inited);
	close_fd(data, "bash", &data -> prev_pipes);
	print_err(data, err_msg, cmd, type);
	free_all(data, data -> status);
}

void	is_error(t_data *data, void *elem, char *err_msg, int type)
{
	if (!elem)
		print_err_and_exit(data, elem, err_msg, type);
}
