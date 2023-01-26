/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 21:24:35 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/26 22:32:42 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	copy_tab_to_str(char **tab, char *to_clean)
{
	size_t	i;
	size_t	j;
	size_t	k;

	k = -1;
	i = -1;
	while (tab[++i])
	{
		j = -1;
		while (tab[i][++j])
		{
			if (tab[i][j] == ' ')
				to_clean[++k] = tab[i][j] * -1;
			else
				to_clean[++k] = tab[i][j];
		}
		if (tab[i + 1])
			to_clean[++k] = ' ';
	}
}
void	back_to_space(char **tab)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (tab[++i])
	{
		j = -1;
		while (tab[i][++j])
		{
			if (tab[i][j] < 0)
				tab[i][j] *= -1;
		}
	}
}
void	expanded_tab(t_cmd *cmd, char **tab)
{
	size_t	len;
	char	*to_clean;

	len = ft_str_tab_len(tab) + ft_tab_len(tab);
	to_clean = ft_calloc(sizeof(char), len + 1);
	is_error(cmd -> data, to_clean, MALLOC_ERR, 0);
	copy_tab_to_str(tab, to_clean);
	cmd -> args = ft_free_tab(tab);
	to_clean = clean_(cmd -> data, to_clean, 1);
	tab = ft_split(to_clean, ' ');
	is_error(cmd -> data, tab, MALLOC_ERR, 0);
	ft_free_elem((void **)&to_clean);
	back_to_space(tab);
	cmd -> args = tab;
	cmd -> cmd = tab[0];
}

int	check_tab(char **tab)
{
	size_t	i;
	size_t	j;
	int		quotes;

	quotes = 0;
	i = -1;
	while (tab[++i])
	{
		j = -1;
		while (tab[i][++j])
		{
			if (tab[i][j] == '$')
				return (1);
			else if (tab[i][j] < 0)
				quotes = -1;
		}
	}
	return (quotes);
}

char	*clean_lines(t_data *data, char *line, int expand)
{
	size_t	i;

	i = -1;
	if (line == NULL)
		return (line);
	while (line[++i])
	{
		if (expand && line[i] == '$')
			return (clean_(data, line, 1));
		if (expand == 0 && line[i] < 0)
			return (clean_(data, line, 0));
	}
	return (line);
}

void	clean_cmd(t_cmd *cmd)
{
	int		to_clean;
	size_t	i;
	char	**tab;

	i = -1;
	if (cmd -> args == NULL)
		return ;
	tab = cmd -> args;
	to_clean = check_tab(cmd -> args);
	if (to_clean < 0)
		while (tab[++i])
			tab[i] = clean_lines(cmd -> data, tab[i], 0);
	else if (to_clean > 0)
		expanded_tab(cmd, cmd -> args);
	if (to_clean > 0 && cmd -> cmd && cmd -> args[0] != cmd -> cmd)
		ft_free_elem((void **)&cmd -> cmd);
	cmd -> cmd = cmd -> args[0];
	init_path(cmd);
	cmd -> to_not_calloc = 1;
}

void	loop_files(t_data *data, t_files **tab)
{
	size_t	i;
	size_t	j;
	char	*to_clean;
	
	i = -1;
	while (tab[++i])
	{
		j = -1;
		if (tab[i]-> type != DOC)
		{
			to_clean = tab[i]-> files;
			tab[i]-> amb = -(to_clean[0] == '"' * -1) * to_clean[0];
			while (to_clean[++j])
			{
				if ((to_clean[j] == '$' 
					&& !check_dollars(to_clean[j + 1], to_clean, j)) || to_clean[j] < 0)
				{
					tab[i]-> amb += (ft_strchr(&to_clean[j], '$') != NULL) * '$';
					tab[i]-> files = clean_(data, to_clean, 1);
					tab[i]-> amb += (ft_strlen(tab[i]-> files) == 0);
					break ;
				}
			}
		}
		else
			tab[i]-> files = clean_lines(data, tab[i]-> files, 0);
	}
}

void    clean_files(t_cmd *cmd)
{
    if (cmd -> tab)
	{
		loop_files(cmd -> data, cmd -> tab);
		set_last_setup(cmd);
		cmd -> to_not_calloc = 1;
	}
}