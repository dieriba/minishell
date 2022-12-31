/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 19:28:43 by dtoure            #+#    #+#             */
/*   Updated: 2022/12/31 02:52:39 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

void	check_files(char *files, char *err, int flags)
{
	if (access(files, flags))
		print_err_and_exit(data, err, 1);
}