/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expand_files.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 03:40:35 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/07 03:48:57 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	expand_args(t_cmd *cmd)
{
	DIR	*directory;

	directory = opendir(".");
	if (dir == NULL)
		return ;
}