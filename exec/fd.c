/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:28:59 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/24 02:39:04 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_fd(t_data *data, char *str, int *fd)
{
	if ((*fd) == -1)
		return ;
	if (close((*fd)) < 0)
		print_err_and_exit(data, NULL, str, 1);
	(*fd) = -1;
}

void	check_files(t_data *data, t_files **tab, int flags)
{
	int	i;

	i = -1;
	if (tab == NULL)
		return ;
	while (tab[++i])
	{
		if (tab[i]-> amb || tab[i]-> type == IN)
		{
			if (access(tab[i]-> files, flags))
				print_err_and_exit(data, NULL, "bash", 1);
		}
	}
}

void	open_files(t_data *data, t_cmd *cmd)
{
	t_files	**tab;
	int		i;
	
	i = -1;
	tab = cmd -> tab;
	while (tab[++i])
	{
		if ((tab[i]-> files != cmd -> last_out -> files) 
			&& (tab[i]-> type == OUT || tab[i]-> type == APPEND))
		{
			if (open(tab[i]-> files, tab[i]-> flags, 0644) < 0)
				print_err_and_exit(data, NULL, "bash", 1);
		}
	}
}

int	opener_outfile(t_cmd *cmd)
{
	t_data	*data;
	t_files	*last;
	int		fd;

	data = cmd -> data;
	last = cmd -> last_out;
	open_files(data, cmd);
	fd = open(last -> files, last -> flags, 0666);
	return (fd);
}
