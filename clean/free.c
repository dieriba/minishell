/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 20:32:53 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/23 20:43:40 by dtoure           ###   ########.fr       */
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

	i = -1;
	if (!cmds)
		return ;
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
		free(node);
		node = next;
	}
	(*head) = NULL;
	if (env)
		free(env);
}

void	free_all(t_data *data, int status, int free_)
{
	free_list(data -> env, &data -> env -> start);
	if (data -> cp_to_parse)
		free(data -> cp_to_parse);
	if (data -> here_doc_opened && data -> here_doc_closed == 0)
		close_all_pipes(data, &data -> here_docs, 1, 0);
	if (free_)
		free_cmd(data -> cmds);
	free(data);
	exit(status);
}
