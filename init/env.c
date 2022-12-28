/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 21:38:42 by dtoure            #+#    #+#             */
/*   Updated: 2022/12/28 22:30:09 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*char	*get_path(t_data *data, char *var)
{
	char	*res;
		
	return (res);	
}*/

void	set_env(t_data *data, char **envp)
{
	data -> env = ft_calloc(sizeof(t_env), 1);
	is_error(data, data -> env, MALLOC_ERR);
	create_list(data, envp);
	print_env(data -> env -> start);
}