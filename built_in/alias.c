/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:11:03 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/11 16:46:40 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*is_valid_alias(char *line)
{
	size_t	i;

	i = -1;
	while (line[++i] && line[i] != '=')
		;
	if (line[i] == 0)
		return (line);
	line[i] = 0;
	if (check_line_alias(line))
	{
		line[i] = '=';
		return (line);
	}
	line[i] = '=';
	return (&line[i]);
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
	t_node	*alias;
	size_t	i;

	node = create_node(data, line, 1);
	is_error(data, node, MALLOC_ERR, 0);
	i = ft_char_index(line, '=');
	line[i] = 0;
	alias = find_(data, line);
	line[i] = '=';
	node -> i = ++i;
	if (set_up_alias(data, node, alias))
		return ;
	data -> status = 0;
}

void	handle_alias(t_data *data, t_cmd *cmd)
{
	int		i;
	char	*line;

	i = 0;
	while (cmd -> args[++i])
	{
		if (!check_alias(data -> alias -> head, cmd -> args[i]))
		{
			line = is_valid_alias(cmd -> args[i]);
			if (line && line != cmd ->args[i])
				export_alias(data, cmd -> args[i]);
			else if (line && line == cmd -> args[i])
				alias_(data, cmd, line);
		}
	}
}

int	alias(t_data *data, t_cmd *cmd)
{
	int		len;

	data -> status = 0;
	if (open_check_files_built_in(cmd, cmd -> tab))
		return (1);
	len = ft_tab_len(cmd -> args);
	if (len > 1 && ((!ft_strcmp(cmd -> stop, "|")
				|| !ft_strcmp(cmd -> prev_stop, "|"))))
		return (print_err_built_in(cmd, "bash", -1));
	if (len == 1)
		return (print_alias(data, cmd));
	else if (len > 1)
		handle_alias(data, cmd);
	if (cmd && cmd -> last_in && cmd -> last_in -> type == IN)
		close_fd_built_in(&cmd -> last_in -> fd);
	if (cmd && cmd -> last_out)
		close_fd_built_in(&cmd -> last_out -> fd);
	return (1);
}
