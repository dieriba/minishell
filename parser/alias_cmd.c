/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 16:50:55 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/10 23:44:12 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	join_line(t_data *data, char **tmp, char *line)
{
	t_node	*alias;
	char	*to_free;

	to_free = (*tmp);
	alias = find_(data, line);
	if (alias)
		(*tmp) = ft_strjoin((*tmp), &alias -> line[alias -> i], 0, 0);
	else
		(*tmp) = ft_strjoin((*tmp), line, 0, 0);
	ft_free_elem((void **)&to_free);
	is_error(data, (*tmp), MALLOC_ERR, 0);
}

void	from_line_to_hero(t_data *data, char *line, char **tmp)
{
	size_t	i;
	size_t	j;
	char	stop;

	i = -1;
	while (line[++i])
	{
		if (!ft_isspace(line[i]))
		{
			j = i;
			while (line[++i] && !ft_isspace(line[i]))
				;
			i += (line[i] != 0);
			stop = line[i];
			line[i] = 0;
			join_line(data, tmp, &line[j]);
			line[i] = stop;
			i--;
		}
		if (line[i] == 0)
			break ;
	}
	ft_free_elem((void **)&line);
}

void	from_alias_to_hero(t_data *data, t_cmd *cmd, char **tab)
{
	char	*line;
	char	*tmp;

	tmp = NULL;
	if (!ft_strcmp(tab[0], "unalias") || !ft_strcmp(tab[0], "alias")
		|| !ft_strcmp(tab[0], "cd"))
		return ;
	line = find_alias_node(data, tab[0]);
	if (line)
	{
		line = from_tab_to_line(cmd, tab);
		from_line_to_hero(data, line, &tmp);
		cmd -> args = ft_split(tmp, ' ');
		is_error(data, cmd -> args, MALLOC_ERR, 0);
		ft_free_elem((void **)&tmp);
		return ;
	}
}
