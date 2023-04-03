/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:28:59 by dtoure            #+#    #+#             */
/*   Updated: 2023/03/27 13:44:52 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_all(t_data *data, t_cmd *cmd)
{
	if (cmd -> last_in && cmd -> last_in -> type == IN)
		close_fd(cmd -> data, "minishell4", &cmd -> last_in -> fd);
	if (cmd -> last_out)
		close_fd(data, "minishell5", &cmd -> last_out -> fd);
	close_both_pipes(data, data -> pipes, &data -> inited);
	clean_s_pipes(data);
	close_fd(data, "minishell6", &data -> prev_pipes);
	close_all_pipes(data, &data -> here_docs, 1, 0);
}

void	close_fd(t_data *data, char *str, int *fd)
{
	if ((*fd) == -1)
		return ;
	if (close((*fd)) < 0)
		print_err_and_exit(data, NULL, str, 1);
	(*fd) = -1;
}

void	close_all_fds(t_files **tab)
{
	size_t	i;

	i = -1;
	while (tab[++i])
	{
		if (tab[i]-> fd > 0)
			close(tab[i]-> fd);
	}
}

void	open_files(t_data *data, t_cmd *cmd, t_files *files)
{
	enum e_type	type;
	t_files		*last_in;
	t_files		*last_out;

	last_in = cmd -> last_in;
	last_out = cmd -> last_out;
	type = files -> type;
	files -> fd = open(files -> files, files -> flags, 0644);
	if (files -> fd == -1)
	{
		close_all_fds(cmd -> tab);
		print_err_and_exit(data, NULL, "minishell", 1);
	}
	if (last_in && type == IN && files -> files != last_in -> files)
		close_fd(data, "minishell", &files -> fd);
	else if (last_out && type != IN && files -> files != last_out -> files)
		close_fd(data, "minishell", &files -> fd);
}

void	open_check_files(t_data *data, t_cmd *cmd, t_files **tab)
{
	size_t		i;
	enum e_type	type;

	i = -1;
	if (cmd -> last_in == NULL && cmd -> last_out == NULL)
		return ;
	cmd -> data -> status = 1;
	while (tab[++i])
	{
		type = tab[i]-> type;
		if (type != DOC && tab[i]-> amb == DOLLARS_EMPT)
			print_err_and_exit(data, NULL, AMB_REDIRECT, 0);
		else if ((type == OUT || type == APPEND) && tab[i]-> amb == ALL_FLAGS)
		{	
			if (access(tab[i]-> files, F_OK))
				print_err_and_exit(data, NULL, "minishell", 1);
		}
		else if (type != DOC)
			open_files(data, cmd, tab[i]);
	}
	cmd -> data -> status = 0;
}

int	find_fd(t_doc *node, char *limiter)
{
	while (node)
	{
		if (node -> limiter == limiter)
			break ;
		node = node -> next;
	}
	return (node -> pipes[0]);
}
