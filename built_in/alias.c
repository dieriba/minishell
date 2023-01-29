/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:11:03 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/29 06:28:53 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char	*is_valid_alias(char *line)
{
	size_t	i;

	i = -1;
	while (line[++i] && line[i] != '=')
		;
	if (line[i] == 0)
		return (line);
	line[i] = 0;
	if (check_line(line))
	{
		line[i] = '=';
		return (line);
	}
	line[i] = '=';
	return (&line[i]);
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
	else if (data -> alias -> last == alias)
		data -> alias -> last = node;
}

void	set_node_alias(t_data *data, t_node *node)
{
	data -> alias -> last -> next = node;
	node -> prev = data -> alias -> last;
	data -> alias -> last = node;
}

void	export_alias(t_data *data, char *line)
{
	t_node	*node;
	size_t	i;
	t_node	*alias;

	node = create_node(data, line, 1);
	is_error(data, node, MALLOC_ERR, 0);
	if (data -> alias -> head == NULL)
	{
		data -> alias -> head = node;
		data -> alias -> last = node;
		return ;
	}
	i = ft_char_index(line, '=');
	line[i] = 0;
	alias = find_(data, line);
	line[i] = '=';
	node -> i = ++i;
	if (alias)
	{
		set_alias(data, node, alias);
		ft_free_elem((void **)&alias -> line);
		ft_free_elem((void **)&alias);
	}
	else
		set_node_alias(data, node);
	data -> status = 0;
}

void	alias(t_data *data, t_cmd *cmd, int subshell, int fork)
{
	int		len;
	char	*line;
	size_t	i;

	i = 0;
	len = ft_tab_len(cmd -> args);
	if (len == 1 && fork)
		print_alias(cmd -> data, cmd, subshell);
	else if (len > 1 && fork == 0 && ft_strcmp(cmd -> stop, "|"))
	{
		while (cmd -> args[++i]
			&& !check_alias(data -> alias -> head, cmd -> args[i]))
		{
			line = is_valid_alias(cmd -> args[i]);
			if (line && line != cmd ->args[i])
				export_alias(data, cmd -> args[i]);
			else if (line && line == cmd -> args[i])
				alias_(data, cmd, line, subshell);
		}
	}
}
