/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 06:02:28 by dtoure            #+#    #+#             */
/*   Updated: 2022/12/27 06:18:05 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env(t_env *env)
{
    t_line  *line;

    line = env -> first;
    while (line)
    {
        ft_putstr_fd(line -> line, 1);
        line = line -> next;
    }
}