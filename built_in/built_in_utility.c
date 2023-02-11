/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utility.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 23:06:45 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/11 13:44:12 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	print_err_built_in(t_cmd *cmd, char *str, int type)
{
	if (cmd && cmd -> last_in && cmd -> last_in -> type == IN)
		close_fd_built_in(&cmd -> last_in -> fd);
	if (cmd && cmd -> last_out)
		close_fd_built_in(&cmd -> last_out -> fd);
	if (type > 0)
		perror(str);
	else if (type == 0 && ft_putstr_fd(str, 2) < 0)
		return (-1);
	return (1);
}

int	close_fd_built_in(int *fd)
{
	if (close(*fd) < 0)
		return (1);
	return (0);
}

int	open_files_built_in(t_cmd *cmd, t_files *files)
{
	enum e_type	type;
	t_files		*last_in;
	t_files		*last_out;

	last_in = cmd -> last_in;
	last_out = cmd -> last_out;
	type = files -> type;
	files -> fd = open(files -> files, files -> flags, 0644);
	if (files -> fd == -1)
		return (1);
	if (last_in && type == IN && files -> files != last_in -> files)
		return (close_fd_built_in(&files -> fd));
	else if (last_out && type != IN && files -> files != last_out -> files)
		return (close_fd_built_in(&files -> fd));
	return (0);
}

int	open_check_files_built_in(t_cmd *cmd, t_files **tab)
{
	size_t		i;
	enum e_type	type;

	i = -1;
	if (cmd -> last_in == NULL && cmd -> last_out == NULL)
		return (0);
	cmd -> data -> status = 1;
	while (tab[++i])
	{
		type = tab[i]-> type;
		if (type != DOC && tab[i]-> amb == DOLLARS_EMPT)
			return (print_err_built_in(NULL, AMB_REDIRECT, 0));
		else if ((type == OUT || type == APPEND) && tab[i]-> amb == ALL_FLAGS)
		{	
			if (access(tab[i]-> files, F_OK))
				return (print_err_built_in(NULL, "bash", 1));
		}
		else if (type != DOC && open_files_built_in(cmd, tab[i]))
			return (print_err_built_in(NULL, "bash", 1));
	}
	cmd -> data -> status = 0;
	return (0);
}
