/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expand_files.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 03:40:35 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/07 04:14:47 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	len_object(void)
{
	DIR				*directory;
	struct dirent	*object;
	int				len;

	len = 0;
	directory = opendir(".");
	if (dir == NULL)
		return ;
	object = readdir(directory)
	while (object)
	{
		len++;
		object = readdir(rec)
	}
	return (len);
}

void	expand_args(t_data *data, t_cmd *cmd)
{
	DIR				*directory;
	struct dirent	*object;
	
	directory = opendir(".");
	if (dir == NULL)
		return ;
	object = readdir(directory)
	while (object)
	{
		
		object = readdir(rec)
	}
	if (close(dir) < 0)
		print_err_and_exit(data, NULL, "bash", 1);
}