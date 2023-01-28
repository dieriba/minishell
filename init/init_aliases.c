/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_aliases.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 04:28:31 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/28 05:38:38 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_aliases(t_data *data, t_node *node)
{
	while (node)
	{
		if (ft_putendl_fd(node -> line, 1) < 0)
			print_err_and_exit(data, NULL, "syscall", 1);
		node = node -> next;
	}
}

void	read_file(t_data *data, int fd)
{
	char	*line;
	t_node	*node;
	size_t	i;

	i = -1;
	while (1)
	{
		line = get_next_line(fd, 1);
		if (!line)
			break ;
		while (line[++i] && line[i] != '\n')
			;
		line[i] = 0;
		node = create_node(data, line, 1);
		is_error(data, node, MALLOC_ERR, 0);
		ft_lst_add_front_s(&data -> alias -> head, node);
		ft_free_elem((void **)&line);
		i = -1;
	}
	get_next_line(fd, 0);
	if (line)
		ft_free_elem((void **)&line);
	close_fd(data, "bash", &fd);
}

void	last_node(t_data *data)
{
	t_node	*node;

	node = data -> alias -> head;
	while (node -> next)
		node = node -> next;
	data -> alias -> last = node;
}

void	populate(t_data *data, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY, 0644);
	if (fd > 0)
	{
		data -> alias = ft_calloc(sizeof(t_alias), 1);
		is_error(data, data -> alias, MALLOC_ERR, 1);
		read_file(data, fd);
		last_node(data);
	}
}