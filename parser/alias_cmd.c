/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 16:50:55 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/16 01:01:04 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	from_alias_to_hero(t_data *data, t_cmd *cmd, char **tab)
{
	t_node	*alias;
	char	*tmp;
	size_t	i;
	char	*line;

	tmp = NULL;
	if (!ft_strcmp(tab[0], "unalias") || !ft_strcmp(tab[0], "alias")
		|| !ft_strcmp(tab[0], "cd"))
		return ;
	alias = find_(data, tab[0]);
	if (alias)
	{
		i = ft_strlen(cmd -> args[0]);
		line = from_tab_to_line(cmd, cmd -> args);
		tmp = ft_strjoin(&alias -> line[alias -> i], &line[i], " ", 0);
		is_error(data, tmp, MALLOC_ERR, 0);
		set_commands(cmd, tmp);
		ft_free_elem((void **)&tmp);
		ft_free_elem((void **)&line);
		return ;
	}
}
