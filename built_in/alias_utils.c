/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:38:58 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/24 11:32:36 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_alias_node(t_data *data, t_cmd *cmd, char *line)
{
	int	fd;

	fd = where_to_write(data, cmd);
	if (ft_putendl_fd(line, fd) < 0)
		print_err_and_exit(data, NULL, "syscall", 0);
}

char	*find_alias_node(t_data *data, char *line)
{
	t_node	*node;

	if (data -> alias == NULL)
		return ((NULL));
	node = data -> alias -> head;
	while (node)
	{
		if (!check(node -> line, line))
			return (node -> line);
		node = node -> next;
	}
	return (NULL);
}

void	print_err_alias(t_data *data, char *line)
{
	int	saved_stdout;
	int	saved_stderr;

	saved_stderr = dup(STDERR_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdout < 0 || saved_stderr < 0)
		print_err_and_exit(data, NULL, "syscall", 1);
	dup_and_close(data, STDERR_FILENO, STDOUT_FILENO, STDERR_FILENO);
	if (ft_printf("minishell : alias: %s : invalaid alias name\n", line) < 0)
		print_err_and_exit(data, NULL, "syscall", 0);
	dup_and_close(data, saved_stdout, STDOUT_FILENO, saved_stdout);
	dup_and_close(data, saved_stderr, STDERR_FILENO, saved_stderr);
}

void	alias_(t_data *data, t_cmd *cmd, char *line)
{
	size_t	i;
	char	*res;

	i = -1;
	while (line[++i] && line[i] != '=')
		;
	if (line[i])
	{
		print_err_alias(data, line);
		return ;
	}
	res = find_alias_node(data, line);
	handle_alias_node(data, cmd, res, line);
	data -> status = 1;
}

int	print_alias(t_data *data, t_cmd *cmd)
{
	t_node	*node;
	int		fd;

	data -> status = 1;
	node = data -> alias -> head;
	fd = where_to_write(data, cmd);
	while (node)
	{
		if (ft_putendl_fd(node -> line, fd) < 0)
			return (print_err_built_in(cmd, "syscall", 1));
		node = node -> next;
	}
	if (cmd && cmd -> last_in && cmd -> last_in -> type == IN)
		close_fd_built_in(&cmd -> last_in -> fd);
	if (cmd && cmd -> last_out)
		close_fd_built_in(&cmd -> last_out -> fd);
	data -> status = 0;
	return (1);
}
