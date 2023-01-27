/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 20:32:53 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/27 01:41:47 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_files(t_files **tab)
{
	size_t	i;

	i = -1;
	while (tab[++i])
	{
		free(tab[i]-> files);
		free(tab[i]);
	}
	free(tab);
}

void	free_cmd(t_cmd **cmds)
{
	size_t	i;
	t_data	*data;

	if (!cmds)
		return ;
	data = cmds[0]-> data;
	i = -1;
	while (cmds[++i])
	{
		if (cmds[i]-> args && cmds[i]-> cmd != cmds[i]-> args[0])
			free(cmds[i]-> cmd);
		if (cmds[i]-> args)
			ft_free_tab(cmds[i]-> args);
		if (cmds[i]-> tab)
			free_files(cmds[i]-> tab);
		if (cmds[i]-> paths)
			ft_free_tab(cmds[i]-> paths);
		free(cmds[i]);
	}
	free(cmds);
	data -> cmds = NULL;;
}

void	free_list(t_env *env, t_node **head)
{
	t_node	*next;
	t_node	*node;

	if (!head)
		return ;
	node = (*head);
	while (node)
	{
		next = node -> next;
		node -> next = NULL;
		node -> prev = NULL;
		if (node -> alloc && node -> line)
			free(node -> line);
		ft_free_elem((void **)&node);
		node = next;
	}
	(*head) = NULL;
	if (env)
		free(env);
}

void	free_all(t_data *data, int status)
{
	data -> tab_ = ft_free_tab(data -> tab_);
	data -> envp = ft_free_tab(data -> envp);
	if (data -> subshell)
	{
		close_one_end(data, data -> p_pipes, 1, &data -> s_pipes_inited);
		close_one_end(data, data -> p_pipes, 0, &data -> s_pipes_inited);
	}
	free_cmd(data -> cmds);
	ft_free_elem((void **)&g_collector);
	ft_free_elem((void **)&data -> cp_to_parse);
	ft_free_elem((void**)&data -> env);
	clean_here_doc(data, &data -> here_docs);
	free(data);
	exit(status);
}
