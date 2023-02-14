/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expand_files_utility.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 01:36:13 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/14 13:27:21 by dtoure           ###   ########.fr       */
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

int	glob_args(char *line)
{
	size_t	i;

	i = -1;
	while (line[++i])
	{
		if ((line[i] == '"' && valid_double(line, i))
			|| line[i] == '\'')
			skip_(line, &i, line[i]);
		else if (line[i] == '*')
			return (1);
	}
	return (0);
}

int	glob_character_(char **tab)
{
	int		i;

	i = -1;
	if (tab == NULL)
		return (0);
	while (tab[++i])
	{
		if (glob_args(tab[i]))
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

/*void	ascii_sort_list(t_node **args_expands)
{
	
}*/