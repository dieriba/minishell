/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:46:00 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/23 22:16:44 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	struct sigaction	sig;

	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	sig.sa_handler = exit_;
	sigaction(SIGINT, &sig, NULL);
	node = (*head);
	while (node)
	{
		while (1)
		{
			line = readline("here_doc: ");
			if (!line || !ft_strcmp(node -> limiter, line))
				break ;
			ft_putendl_fd(line, node -> pipes[1]);
		}
		node = node -> next;
	}
	close_all_pipes(data, head, 1, 1);
	free(g_collector);
	exit(EXIT_SUCCESS);
}

void	fork_docs(t_data *data, t_doc **head)
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
		if (WIFEXITED(status))
			data -> status = WEXITSTATUS(status);
	}
}
