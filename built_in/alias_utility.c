/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_utility.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 23:10:28 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/24 11:32:29 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_line_alias(char *line)
{
	size_t	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '$'
			&& (line[i + 1] == '=' || !line[i]))
			return (1);
		if (!ft_strchr(ALIAS_AUTHORIZED, line[i])
			&& !ft_isalpha(line[i]))
			return (1);
	}
	return (0);
}

void	set_alias(t_data *data, t_node *node, t_node *alias)
{
	node -> prev = alias -> prev;
	node -> next = alias -> next;
	if (alias -> prev)
		alias -> prev -> next = node;
	if (alias -> next)
		alias -> next -> prev = node;
	if (data -> alias -> head == alias)
		data -> alias -> head = node;
	if (data -> alias -> last == alias)
		data -> alias -> last = node;
}

int	set_up_alias(t_data *data, t_node *node, t_node *alias)
{
	if (data -> alias -> head == NULL)
	{
		data -> alias -> head = node;
		data -> alias -> last = node;
		return (1);
	}
	if (alias)
	{
		set_alias(data, node, alias);
		ft_free_elem((void **)&alias -> line);
		ft_free_elem((void **)&alias);
	}
	else
		set_node_alias(data, node);
	return (0);
}

int	check_alias(t_node *alias, char *line)
{
	while (alias)
	{
		if (alias -> line[0] == line[0]
			&& !ft_strcmp(alias -> line, line))
			return (1);
		alias = alias -> next;
	}
	return (0);
}

void	handle_alias_node(t_data *data, t_cmd *cmd, char *res, char *line)
{
	int		saved_stdout;
	int		saved_stderr;

	if (res == NULL)
	{
		saved_stdout = dup(STDOUT_FILENO);
		saved_stderr = dup(STDERR_FILENO);
		if (saved_stdout < 0 || saved_stderr < 0)
			print_err_and_exit(data, NULL, "syscall", 1);
		dup_and_close(data, STDERR_FILENO, STDOUT_FILENO, STDERR_FILENO);
		if (ft_printf("minishell : alias: %s : not found\n", line) < 0)
			print_err_and_exit(data, NULL, "syscall", 1);
		dup_and_close(data, saved_stdout, STDOUT_FILENO, saved_stdout);
		dup_and_close(data, saved_stderr, STDERR_FILENO, saved_stderr);
	}
	else if (res)
		print_alias_node(data, cmd, res);
}
