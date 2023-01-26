/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 04:30:31 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/26 16:53:47 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    make_some_space(t_env *env, char *line)
{
	char	**tmp_tab;
    size_t	i;
	
	i = -1;
    tmp_tab = ft_calloc(env -> len + CAPACITY + 1, sizeof(char *));
	is_error(env -> data, tmp_tab, MALLOC_ERR, 0);
	while (env -> tab[++i])
	{
		tmp_tab[i] = ft_strdup(env -> tab[i]);
		if (!tmp_tab[i])
			tmp_tab = ft_free_tab(tmp_tab);
		is_error(env -> data, tmp_tab[i], MALLOC_ERR, 0);
	}
	env -> tab = ft_free_tab(env -> tab);
	tmp_tab[i] = ft_strdup(line);
	is_error(env -> data, tmp_tab[i], MALLOC_ERR, 0);
	env -> capacity = CAPACITY;
	env -> tab = tmp_tab;
	env -> data -> envp = env -> tab;
	env -> data -> path = find_var(env -> tab, "PATH");
}

int		find_var_index(char **tab, char *to_find, int len)
{
	int  i;
    int  j;

    j = -1;
	i = -1;
    while (to_find[++j] && to_find[j] != '=')
        ;
    to_find[j] = 0;
	while (tab[++i])
		if (!check(tab[i], to_find))
			break ;		
    to_find[j] = '=';
	if (len == i)
		return (-1);
	return (i);
}

void	make_export(t_env *env, char *line)
{
    int index;

    index = find_var_index(env -> tab, line, env -> len);
    if (index > -1)
    {
        ft_free_elem((void **)&env -> tab[index]);
        env -> tab[index] = ft_strdup(line);
        is_error(env -> data, env -> tab[index], MALLOC_ERR, 0);
    }
	else if (env -> capacity)
	{
		env -> tab[env -> len] = ft_strdup(line);
		is_error(env -> data, env -> tab[env -> len], MALLOC_ERR, 0);
		env -> len++;
		env -> capacity--;
	}
	else
        make_some_space(env, line);
	env -> data -> status = 0;
}