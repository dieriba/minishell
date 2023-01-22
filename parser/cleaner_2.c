/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 21:24:35 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/22 23:50:13 by dtoure           ###   ########.fr       */
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
	printf("Before 1 %s\n", to_clean);
	copy_tab_to_str(tab, to_clean);
	printf("After 1 %s\n", to_clean);
	ft_free_tab(tab);
	printf("Before 2 %s\n", to_clean);
	to_clean = clean_(cmd -> data, to_clean);
	printf("After 2 %s\n", to_clean);
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
	printf("Entered cmd\n");
	to_clean = check_tab(cmd -> args);
	printf("Value of to_clean cmd : %d\n", to_clean);
	if (to_clean < 0)
		clean_lines(cmd -> data, cmd -> args);
	else if (to_clean > 0)
		expanded_tab(cmd, cmd -> args);
	cmd -> cmd = cmd -> args[0];
}

void    clean_files(t_cmd *cmd)
{
    if (cmd -> in)
	{
		printf("Entered in\n");
        clean_lines(cmd -> data, cmd -> in);
		back_to_space(cmd -> in);
	}
	if (cmd -> out)
	{
        clean_lines(cmd -> data, cmd -> out);
		back_to_space(cmd -> out);
		printf("Entered out\n");
	}
	if (cmd -> out_append)
	{
		printf("Entered app\n");
        clean_lines(cmd -> data, cmd -> out_append);
		back_to_space(cmd -> out_append);
	}
}