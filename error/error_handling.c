/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 17:24:51 by dtoure            #+#    #+#             */
/*   Updated: 2022/12/29 03:48:59 by dtoure           ###   ########.fr       */
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

void	print_err_and_exit(t_data *data, char *err_msg)
{
	if (errno)
		perror("Error");
	else
		ft_putstr_fd(err_msg, 2);
	free_all(data);
}

void	is_error(t_data *data, void *elem, char *err_msg)
{
	if (!elem)
		print_err_and_exit(data, err_msg);
}
