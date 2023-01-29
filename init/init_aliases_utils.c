/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_aliases_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 02:07:20 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/29 02:12:10 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_condition(char *line, int j)
{
	size_t	i;
	int		equal;

	i = -1;
	while (line[++i] && line[i] != '\n')
		;
	line[i] = 0;
	equal = populate_alias(line);
	if (equal < 0)
		equal = log_files_alias(line, equal, j);
	return (equal);
}

void	last_node(t_data *data)
{
	t_node	*node;

	node = data -> alias -> head;
	if (node == NULL)
		return ;
	while (node -> next)
		node = node -> next;
	data -> alias -> last = node;
}
