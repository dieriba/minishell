/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 17:24:51 by dtoure            #+#    #+#             */
/*   Updated: 2022/12/31 23:19:44 by dtoure           ###   ########.fr       */
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

void	print_err(char *str, t_cmd *cmd, int type)
{
	if (errno == 2 && cmd && cmd -> no_path)
	{
		ft_putstr_fd("bash: command not found: ", 2);
		ft_putstr_fd(cmd -> args[0], 2);
		ft_putchar_fd('\n', 2);
		g_data -> status = 127;
	}
	else if (errno == 2 && cmd && !cmd -> no_path)
	{
		ft_putstr_fd("bash: no such file or directory: ", 2);
		ft_putstr_fd(cmd -> cmd, 2);
		ft_putchar_fd('\n', 2);
		g_data -> status = 127;
	}
	else if (type)
		perror(str);
	else
	{
		ft_putstr_fd(str, 2);
		ft_putchar_fd('\n', 2);
	}
}

void	print_err_and_exit(t_cmd *cmd, char *err_msg, int type)
{
	if (g_data -> inited)
	{
		close_fd("bash", g_data -> pipes[0]);
		close_fd("bash", g_data -> pipes[1]);
	}
	if (g_data -> prev_pipes > 0)
		close_fd("bash", g_data -> prev_pipes);
	print_err(err_msg, cmd, type);
	free_all(g_data, g_data -> status);
}

void	is_error(void *elem, char *err_msg, int type)
{
	if (!elem)
		print_err_and_exit(elem, err_msg, type);
}
