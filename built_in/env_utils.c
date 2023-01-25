/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 22:58:15 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/25 13:15:41 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check(char *env, char *to_check)
{
	size_t	i;
	int		res;
	
	i = -1;
	while (env[++i] && env[i] != '=')
		;
	env[i] = 0;
	res = ft_strcmp(env, to_check);
	env[i] = '=';
	return (res);
}

char	*get_var_line(char *line)
{
	size_t	i;

	if (!line)
		return (NULL);
	i = -1;
	while (line[++i] != '=')
		;
	return (&line[++i]);
}

char	*find_var(char **tab, char *to_find)
{
	size_t	i;

	i = -1;
	while (tab[++i])
	{
		if (!check(tab[i], to_find))
			return (tab[i]);
	}
	return (NULL);
}
