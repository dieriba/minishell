/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 17:24:51 by dtoure            #+#    #+#             */
/*   Updated: 2022/12/28 20:50:08 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_all(t_data *data)
{
	free_list(&data -> env -> first);
	free_cmd(data -> cmds);
}

void	print_err_and(t_data *data, char *err_msg)
{
	if (!errno)
		perror("Error");
	free_all(data);
}

void	is_error(t_data *data, void *elem, char *err_msg)
{
	if (!elem)
		print_err_and_exit(data, err_msg);
}