/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_sig_int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:04:55 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/11 18:43:09 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sig_int_fork(int signal)
{
	(void)signal;
	ft_putchar_fd('\n', 0);
	rl_on_new_line();
	rl_redisplay();
	exit(130);
}
