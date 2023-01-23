/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 21:24:35 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/23 22:23:35 by dtoure           ###   ########.fr       */
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
	j = -1;
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
	ft_free_tab(tab);
	to_clean = clean_(cmd -> data, to_clean);
	tab = ft_split(to_clean, ' ');
	is_error(cmd -> data, tab, MALLOC_ERR, 0);
	back_to_space(tab);
	cmd -> args = tab;
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

void	clean_lines(t_data *data, char **tab)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (tab[++i])
	{
		j = -1;
		while (tab[i][++j])
		{
			if (tab[i][j] == '$' || tab[i][j] < 0)
			{
				tab[i] = clean_(data, tab[i]);
				break ;
			}
		}
	}
}


void	clean_cmd(t_cmd *cmd)
{
	int		to_clean;
	
	if (cmd -> args == NULL)
		return ;
	to_clean = check_tab(cmd -> args);
	if (to_clean < 0)
		clean_lines(cmd -> data, cmd -> args);
	else if (to_clean > 0)
		expanded_tab(cmd, cmd -> args);
	cmd -> cmd = cmd -> args[0];
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
			if (to_clean[0] == '"' * -1)
				tab[i]-> amb++;
			while (to_clean[++j])
			{
				if (to_clean[j] == '$' || to_clean[j] < 0)
				{
					tab[i]-> files = clean_(data, to_clean);
					tab[i]-> amb += (ft_strlen(tab[i]-> files) == 0);
					break ;
				}
			}
		}
	}
}

void    clean_files(t_cmd *cmd)
{
    if (cmd -> tab)
        loop_files(cmd -> data, cmd -> tab);
}