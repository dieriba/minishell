/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 06:05:39 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/11 17:41:56 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_index(char **tab, char *to_find)
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

void	remove_var_env(t_env *env, char **tab, int i)
{
	ft_free_elem((void **)&tab[i]);
	while (tab[i + 1])
	{
		tab[i] = tab[i + 1];
		i++;
	}
	if (i > 0 && tab[i] == tab[i - 1])
		tab[i] = tab[i + 1];
	env -> len--;
	env -> capacity++;
	env -> data -> status = 0;
}

int	unset(t_cmd *cmd, t_env *env)
{
	int		index;
	char	*line;
	size_t	i;

	i = 0;
	cmd -> exit_status = 0;
	if (close_redirection(cmd))
		return (1);
	if (!ft_strcmp(cmd -> stop, "|") || !ft_strcmp(cmd -> prev_stop, "|"))
		return (1);
	while (cmd -> args[++i])
	{
		line = find_var(env -> tab, cmd -> args[i]);
		if (line == NULL)
			continue ;
		index = find_index(env -> tab, line);
		remove_var_env(env, env -> tab, index);
	}
	env -> data -> path = find_var(env -> tab, "PATH");
	return (1);
}
