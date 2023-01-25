/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 06:05:39 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/25 13:43:40 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		find_index(char **tab, char *to_find)
{
	size_t	i;

	i = -1;
	while (tab[++i])
	{
		if (!check(tab[i], to_find))
			break ;		
	}
	return (i);
}

void	remove_var_env(char **tab, int i)
{
	ft_free_elem((void **)&tab[i]);
	while (tab[i + 1])
	{
		tab[i] = tab[i + 1];
		i++;
	}
	tab[i] = tab[i + 1];
	arr -> len--;
	arr -> capacity++;
}

void	unset(t_env *env, char *to_find)
{
	int		index;
	char	*line;
	
	line = find_var(env -> tab, to_find);
	if (line == NULL)
		return ;
	index = find_index(env -> tab, line);
	remove_var_env(env -> tab, index);
}
