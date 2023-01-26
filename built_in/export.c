/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 06:30:18 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/26 02:25:14 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_export(t_data *data, t_cmd *cmd, char **tab, int subshell)
{
	size_t	i;
	int		fd;

	fd = where_to_write(data, cmd, subshell);
	i = -1;
	while (tab[++i])
	{
		ft_putstr_fd("export ", fd);
		ft_putendl_fd(tab[i], fd);
	}
	data -> status = 0;
}

void	make_export(t_env *env, char *line)
{
	size_t	i;
	char	**tmp_tab;
	
	i = -1;
	if (env -> capacity)
	{
		env -> tab[env -> len] = ft_strdup(line);
		is_error(env -> data, env -> tab[env -> len], MALLOC_ERR, 0);
		env -> len++;
		env -> capacity--;
	}
	else
	{
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
		env -> capacity = CAPACITY;
		env -> tab = tmp_tab;
	}
	env -> data -> status = 0;
}

int		check_line(char *line)
{
	size_t	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] != '_' && !ft_isalpha(line[i]))
			return (1);
	}
	return (0);
}

char	*is_valid_export(char **tab, char *line)
{
	size_t	i;
	size_t	j;
	
	i = -1;
	j = -1;
	while (tab[++j])
		if (tab[j][0] == line[0] && !ft_strcmp(tab[j], line))
			return (NULL);
	while (line[++i] && line[i] != '=')
		;
	if (line[i] == 0 && check_line(line) == 0)
		return (NULL);
	line[i] = 0;
	if (ft_strlen(line) == 0 || check_line(line))
	{
		line[i] = '=';
		return (line);
	}
	line[i] = '=';
	return (&line[i]);
}

void	export_error(t_data *data, char *line)
{
	ft_putstr_fd("bash: export: `", 2);
	ft_putstr_fd(line, 2);
	ft_putendl_fd("' : not a valid identifier", 2);
	data -> status = 1;
}

void	export(t_cmd *cmd, t_env *env, int fork, int subshell)
{
	int		len;
	char	*line;
	size_t	i;
	
	i = 0;
	len = ft_tab_len(cmd -> args);
	if (len == 1 && fork)
		print_export(cmd -> data, cmd, env -> tab, subshell);
	else if (len > 1 && fork == 0 && ft_strcmp(cmd -> stop, "|"))
	{
		while (cmd ->args[++i])
		{
			line = is_valid_export(env -> tab, cmd ->args[i]);
			if (line && line != cmd ->args[i])
				make_export(env, cmd -> args[i]);
			else if (line && line == cmd ->args[i])
				export_error(cmd -> data, line);	
		}
	}
}
