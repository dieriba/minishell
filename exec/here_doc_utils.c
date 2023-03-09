/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 19:12:57 by dtoure            #+#    #+#             */
/*   Updated: 2023/03/09 03:51:23 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	len_files_tab(t_files **tab)
{
	int	len;

	len = -1;
	if (!tab)
		return (0);
	while (tab[++len])
		;
	return (len);
}

void	ft_lst_add_front_(t_doc **node, t_doc *new)
{
	if (!(*node))
		*(node) = new;
	else
	{
		new -> next = *(node);
		(*node)-> prev = new;
		(*node) = new;
	}
}

int	tab_len(t_cmd **cmds)
{
	size_t	i;

	i = -1;
	while (cmds[++i])
		;
	return (i);
}

int	open_pipes(t_data *data, t_doc **head)
{
	t_doc	*node;

	node = (*head);
	if ((*head) == NULL)
		return (1);
	while (node)
	{
		if (pipe(node -> pipes) < 0)
			print_err_and_exit(data, NULL, PIPE_INIT_ERROR, 0);
		node = node -> next;
	}
	return (0);
}

void	set_up_signals(void)
{
	struct sigaction	sig;

	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	sig.sa_handler = exit_;
	sigaction(SIGINT, &sig, NULL);
}
