/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:46:00 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/07 19:12:40 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	open_here_doc(t_data *data, t_cmd **cmds)
{
	int	len;

	len = tab_len(data -> cmds);
	while (--len > -1)
	{
		if (cmds[len]-> in_here_doc)
			set_node(data, cmds[len]-> in_here_doc);
	}
}

/*void	exit_(int signal)
{
	
}*/

void	handle_here_doc_pipes(t_data *data, t_doc **head)
{
	char	*line;
	t_doc	*node;

	node = (*head);
/*	struct sigaction sig;
	
	sigemptyset(&sig.sa_mask);
	sig.sa_hanler = exit_;
	sigaction(SIGINT, &sig, NULL);*/
	while (node)
	{
		while (1)
		{
			line = readline("here_doc: ");
			if (!ft_strcmp(node -> limiter, line))
				break ;
			ft_putendl_fd(line, node -> pipes[1]);
		}
		close_fd(data, "bash", node -> pipes[1]);
		close_fd(data, "bash", node -> pipes[0]);
		node = node -> next;
	}
	exit(EXIT_SUCCESS);
}

void	fork_docs(t_data *data, t_doc **head)
{
	int		pid_ret;
	int		status;

	open_pipes(data, doc);
	pid_ret = fork();
	if (pid_ret < 0)
		print_err_and_exit(data, NULL, "Error", 1);
	if (pid_ret == 0)
		handle_here_doc_pipes(data, &data -> here_docs);
	waitpid(pid_ret, &status, 0);
	if (WIFEXITED(status))
		data -> status = WEXITSTATUS(status);
}