/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expand_files_utility.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 01:36:13 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/20 16:22:36 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_tabs_args(t_star **tabs)
{
	int	i;

	i = -1;
	while (tabs[++i])
		ft_free_elem((void **)&tabs[i]);
	free(tabs);
}

int	found_expand_(t_data *data, char *line, size_t *i)
{
	char	*to_check;

	to_check = is_valid_expand(data, line);
	if (to_check == NULL)
		return (0);
	(*i) += skip_next_stop(line) - 1;
	if (glob_args(data, &to_check, 0, 0))
		return (1);
	return (0);
}

int	glob_args(t_data *data, char **line, int dollars, int quotes)
{
	size_t	i;
	int		to_find;
	
	i = -1;
	to_find = 0;
	while ((*line)[++i])
	{
		if (((*line)[i] == '"' && valid_double(*line, i)) || (*line)[i] == '\'')
			quotes = skip_and_check_glob((*line), &i, (*line)[i], '*');
		else if ((*line)[i] == '$' && found_expand_(data, &(*line)[i], &i))
			dollars = 1;
		else if ((*line)[i] == '*')
			to_find = 1;
		if (quotes == -1)
			return (0);
		if ((*line)[i] == 0)
			break ;
	}
	return ((to_find != 0) + (dollars != 0));
}

int	glob_character_(t_data *data, char **tab)
{
	int		i;

	i = -1;
	if (tab == NULL)
		return (0);
	while (tab[++i])
	{
		if (glob_args(data, &tab[i], 0, 0))
			return (1);
	}
	return (0);
}

void	update_list_args(
	t_data *data, t_node **args_expands, char *args, int *len)
{
	t_node	*node;

	(*len) += 1;
	node = create_node(data, args, 1);
	is_error(data, node, MALLOC_ERR, 0);
	ft_lst_add_front_s(args_expands, node);
}
