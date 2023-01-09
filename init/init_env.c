/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 21:38:42 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/09 15:35:36 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*char	*get_path(t_node *node, char *var)
{
	char	*res;
	
	res = 	
	return (res);	
}*/

void	init_env(t_data *data, char **envp)
{
	t_node	*path;

	data -> env = ft_calloc(sizeof(t_env), 1);
	is_error(data, data -> env, MALLOC_ERR, 1);
	create_list(data, envp);
	path = find_var(data -> env -> start, "PATH");
	if (path)
		data -> path = path -> line;
}
