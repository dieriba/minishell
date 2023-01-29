/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:38:58 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/29 05:59:05 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_alias_node(t_data *data, t_cmd *cmd, char *line, int subshell)
{
	int	fd;

	fd = where_to_write(data, cmd, subshell);
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
	if (ft_putstr_fd("bash: alias: `", 2) < 0)
		print_err_and_exit(data, NULL, "syscall", 0);
	else if (ft_putstr_fd(line, 2) < 0)
		print_err_and_exit(data, NULL, "syscall", 0);
	else if (ft_putendl_fd("' : invalid alias name", 2))
		print_err_and_exit(data, NULL, "syscall", 0);
}

void	alias_(t_data *data, t_cmd *cmd, char *line, int subshell)
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
	if (res == NULL)
	{
		if (ft_putstr_fd("bash: alias: ", 2) < 0)
			print_err_and_exit(data, NULL, "syscall", 0);
		else if (ft_putstr_fd(line, 2) < 0)
			print_err_and_exit(data, NULL, "syscall", 0);
		else if (ft_putendl_fd(" : not found", 2))
			print_err_and_exit(data, NULL, "syscall", 0);
	}
	else if (res)
		print_alias_node(data, cmd, res, subshell);
	data -> status = 1;
}

void	print_alias(t_data *data, t_cmd *cmd, int subshell)
{
	t_node	*node;
	int		fd;

	node = data -> alias -> head;
	fd = where_to_write(data, cmd, subshell);
	while (node)
	{
		if (ft_putendl_fd(node -> line, fd) < 0)
			print_err_and_exit(data, NULL, "syscall", 1);
		node = node -> next;
	}
	data -> status = 0;
}
