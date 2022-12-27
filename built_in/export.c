/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 06:30:18 by dtoure            #+#    #+#             */
/*   Updated: 2022/12/27 06:33:40 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	export(t_env *env, char *line)
{
	t_line	*first;

	first = env -> first;
	if (!first)
	{
		first -> line = line;
		return ;
	}
	
}