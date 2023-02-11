/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:46:00 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/11 16:47:58 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_quoted_doc(t_doc *node, char *limiter)
{
	size_t	i;

	i = -1;
	while (limiter[++i])
	{
		if ((limiter[i] == '"' && valid_double(limiter, i))
			|| limiter[i] == '\'')
		{
			node -> quoted = 1;
			break ;
		}
	}
}

void	set_node(t_data *data, t_files **tab)
{
	int		len;
	t_doc	*node;

	len = len_files_tab(tab);
	while (len--)
	{
		if (tab[len]-> type == DOC)
		{
			node = ft_calloc(sizeof(t_doc), 1);
			is_error(data, node, MALLOC_ERR, 0);
			check_quoted_doc(node, tab[len]-> files);
			tab[len]-> files = clean_lines(data, tab[len]-> files, 0);
			node -> limiter = tab[len]-> files;
			ft_lst_add_front_(&data -> here_docs, node);
		}
	}
}

void	open_here_doc(t_data *data, t_cmd **cmds)
{
	int	len;

	len = tab_len(data -> cmds);
	while (--len > -1)
		set_node(data, cmds[len]-> tab);
}

void	handle_here_doc_pipes(t_data *data, t_doc **head)
{
	char				*line;
	t_doc				*node;

	set_up_signals();
	node = (*head);
	while (node)
	{
		while (1)
		{
			line = readline("here_doc: ");
			if (!line || !ft_strcmp(node -> limiter, line))
				break ;
			if (node -> quoted == 0)
				line = clean_lines(data, line, 1);
			ft_putendl_fd(line, node -> pipes[1]);
			ft_free_elem((void **)&line);
		}
		ft_free_elem((void **)&line);
		node = node -> next;
	}
	close_all_pipes(data, head, 1, 1);
	free_all(data, 0);
}

int	fork_docs(t_data *data, t_doc **head)
{
	int		pid_ret;
	int		status;

	status = 0;
	if (open_pipes(data, head) == 0)
	{
		pid_ret = fork();
		if (pid_ret < 0)
			print_err_and_exit(data, NULL, "Error", 1);
		if (pid_ret == 0)
			handle_here_doc_pipes(data, &data -> here_docs);
		waitpid(pid_ret, &status, 0);
		ft_free_elem((void **)&g_collector);
		if (WIFEXITED(status))
		{
			data -> status = WEXITSTATUS(status);
			return (data -> status);
		}
	}
	return (0);
}
