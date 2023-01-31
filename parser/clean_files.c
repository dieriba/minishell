/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 21:24:35 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/31 01:35:08 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_dirt(t_data *data, t_files **tab, char *to_clean, size_t i)
{
	size_t	j;

	j = -1;
	tab[i]-> amb = -(to_clean[0] == '"' * -1) * to_clean[0];
	while (to_clean[++j])
	{
		if ((to_clean[j] == '$'
				&& !check_dollars(
					to_clean[j + 1], to_clean, j)) || to_clean[j] < 0)
		{
			tab[i]-> amb += (ft_strchr(&to_clean[j], '$') != NULL) * '$';
			tab[i]-> files = clean_(data, to_clean, 1);
			tab[i]-> amb += (ft_strlen(tab[i]-> files) == 0);
			break ;
		}
	}
}

void	loop_files(t_data *data, t_files **tab)
{
	size_t	i;

	i = -1;
	while (tab[++i])
	{
		if (tab[i]-> type != DOC)
			remove_dirt(data, tab, tab[i]-> files, i);
	}
}

void	clean_files(t_cmd *cmd)
{
	if (cmd -> tab)
	{
		loop_files(cmd -> data, cmd -> tab);
		set_last_setup(cmd);
		cmd -> to_not_calloc = 1;
	}
}
