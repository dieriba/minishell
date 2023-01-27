/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_files_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 04:18:31 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/27 04:19:56 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	file_type(t_files *redirect, char a, char b)
{
	if (a != b && a == R_IN)
	{
		redirect -> type = IN;
		redirect -> flags = O_RDONLY;
	}
	else if (a != b && a == R_OUT)
	{
		redirect -> type = OUT;
		redirect -> flags = O_CREAT | O_TRUNC | O_WRONLY;
	}
	else if (a == b && a == R_IN)
		redirect -> type = DOC;
	else
	{
		redirect -> type = APPEND;
		redirect -> flags = O_CREAT | O_APPEND | O_WRONLY;
	}
}
