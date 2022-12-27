/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 06:18:46 by dtoure            #+#    #+#             */
/*   Updated: 2022/12/27 06:29:53 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd(void)
{
	char	currend_dir[1024];
	
	getcwd(currend_dir, 1024);
	ft_putstr_fd(currend_dir, 1);
	ft_putchar_fd('\n', 1);
}