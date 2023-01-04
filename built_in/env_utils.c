/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 22:58:15 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/04 01:52:15 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check(char *env, char *to_check, size_t size)
{
	size_t	i;

	i = -1;
	while ((to_check[++i] && env[++i]) && i < size && (to_check[i] == env[i]))
		;
	if (env[i] == '=' && !to_check[i])
		return (1);
	return (0);
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
		if (check(node -> line, to_find, ft_strlen(to_find)))
			return (node);
		node = node -> next;
	}
	return (NULL);
}
