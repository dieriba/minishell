/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 21:38:42 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/30 19:20:19 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_env(t_data *data, t_env *env, char **envp)
{
	size_t	i;

	i = -1;
	env -> tab = ft_calloc(env -> len + CAPACITY + 1, sizeof(char *));
	is_error(data, env -> tab, MALLOC_ERR, 0);
	if (env -> len == 0)
		return ;
	while (envp[++i])
	{
		env -> tab[i] = ft_strdup(envp[i]);
		is_error(data, env -> tab[i], MALLOC_ERR, 0);
	}
}

void	init_env(t_data *data, char **envp)
{
	data -> env = ft_calloc(sizeof(t_env), 1);
	is_error(data, data -> env, MALLOC_ERR, 1);
	data -> env -> len = ft_tab_len(envp);
	data -> env -> capacity = CAPACITY;
	set_env(data, data -> env, envp);
	data -> envp = data -> env -> tab;
	data -> env-> data = data;
}
