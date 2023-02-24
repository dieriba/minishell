/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_aliases.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 04:28:31 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/24 11:33:12 by dtoure           ###   ########.fr       */
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

int	populate_alias(char *line)
{
	int	i;
	int	check;

	i = ft_char_index(line, '=');
	if (i == -1)
		return (-1);
	else if (i == 0)
		return (-2);
	line[i] = 0;
	check = check_line_alias(line);
	line[i] = '=';
	if (check)
		i = -3;
	return (i);
}

void	clean_func(t_data *data, char **line, int fd)
{
	get_next_line(fd, 0);
	if (line)
		ft_free_elem((void **)line);
	close_fd(data, "minishell17", &fd);
}

void	read_file(t_data *data, int fd)
{
	char	*line;
	t_node	*node;
	int		equal;
	int		j;

	j = 0;
	while (1)
	{
		j++;
		line = get_next_line(fd, 1);
		if (!line)
			break ;
		equal = check_condition(line, j);
		if (equal < 0)
			continue ;
		if (equal == -4)
			break ;
		node = create_node(data, line, 1);
		node -> i = equal + 1;
		is_error(data, node, MALLOC_ERR, 0);
		ft_lst_add_front_s(&data -> alias -> head, node);
		ft_free_elem((void **)&line);
	}
	clean_func(data, &line, fd);
}

void	populate(t_data *data, char *file)
{
	int	fd;
	int	log_fd;
	int	saved_stdout;

	fd = open(file, O_RDONLY, 0644);
	if (fd > 0)
	{
		saved_stdout = dup(STDOUT_FILENO);
		if (saved_stdout == -1)
			return ;
		log_fd = open(LOG_FILE, O_CREAT | O_APPEND | O_TRUNC | O_RDWR, 0644);
		if (log_fd == -1)
		{
			dup_and_close(data, saved_stdout, STDOUT_FILENO, fd);
			return ;
		}
		dup_and_close(data, log_fd, STDOUT_FILENO, log_fd);
		read_file(data, fd);
		dup_and_close(data, saved_stdout, STDOUT_FILENO, saved_stdout);
		last_node(data);
	}
}
