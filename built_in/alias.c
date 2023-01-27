/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:11:03 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/27 15:46:09 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_alias(t_data *data, t_cmd *cmd, int subshell)
{
	t_node	*node;
	int		fd;

	node = data -> alias -> head;
	fd = where_to_write(data, cmd, subshell);
	while (node)
	{
		ft_putendl_fd(node -> line, fd);
		node = node -> next;
	}
	data -> status = 0;
}

char	*is_valid_alias(char **tab, char *line)
{
	size_t	i;
	size_t	j;

	i = -1;
	j = -1;
	while (tab[++j])
		if (tab[j][0] == line[0] && !ft_strcmp(tab[j], line))
			return (NULL);
	while (line[++i] && line[i] != '=')
		;
	if (line[i] == 0 && check_line(line) == 0)
		return (line);
	line[i] = 0;
	if (ft_strlen(line) == 0 || check_line(line))
	{
		line[i] = '=';
		return (line);
	}
	line[i] = '=';
	return (&line[i]);
}

void	alias_error(t_data *data, char *line)
{
	ft_putstr_fd("bash: export: `", 2);
	ft_putstr_fd(line, 2);
	ft_putendl_fd("' : not a valid identifier", 2);
	data -> status = 1;
}


void	alias(t_data *data, t_cmd *cmd, int fork, int subshell)
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
		while (cmd ->args[++i])
		{
			line = is_valid_alias(env -> tab, cmd ->args[i]);
			if (line && line != cmd ->args[i])
				export_alias(env, cmd -> args[i]);
			else if (line && line == cmd -> args[i])
				alias_error(cmd -> data, line);
		}
	}
}