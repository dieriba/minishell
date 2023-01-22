/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 22:58:15 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/22 22:52:42 by dtoure           ###   ########.fr       */
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

char	*get_var_line(t_node *node)
{
	size_t	i;

	if (!node)
		return (NULL);
	i = -1;
	while (node -> line[++i] != '=')
		;
	return (&node -> line[++i]);
}

t_node	*find_var(t_node *node, char *to_find)
{
	while (node)
	{
		if (!check(node -> line, to_find))
			return (node);
		node = node -> next;
	}
	return (NULL);
}
