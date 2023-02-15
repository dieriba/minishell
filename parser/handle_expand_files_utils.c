/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expand_files_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 20:01:34 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/15 15:50:41 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	valid_occurence(t_star *args, char *line, char c)
{
	if ((line[0] == '.' && args -> pattern[0] == '.'))
		return (args -> st_bfore);
	else if ((args -> st_after == 0 && c == 0) || (args -> st_after))
		return (0);
	return (1);
}

int	set_new_val(size_t *m, int j, int k)
{
	(*m) = j + k;
	return (0);
}

int	find_occurence(char	*line, int k, size_t *m, t_star *args)
{
	size_t	j;
	int		len;
	int		res;
	int		stop;

	j = (*m);
	while (line[j])
	{
		if (args -> st_bfore)
			while (line[j] && line[j] != args -> pattern[0])
				j++;
		len = ft_strlen(&line[j]);
		if (line[j] == 0 || len - k < 0)
			return (1);
		stop = line[j + k];
		line[j + k] = 0;
		res = ft_strcmp(&line[j], args -> pattern);
		line[j + k] = stop;
		if (args -> st_bfore == 0 && res)
			return (1);
		else if (!res && !valid_occurence(args, line, line[j + k]))
			return (set_new_val(m, j, k));
		j++;
	}
	return (1);
}

int	valid_regex(char *line, t_star **tabs)
{
	int		i;
	size_t	j;
	size_t	k;

	i = -1;
	k = 0;
	if (tabs[0] == NULL)
		return (1);
	while (tabs[++i])
	{
		j = ft_strlen(tabs[i]-> pattern);
		if (j > ft_strlen(&line[k]) || j == 0)
			return (1);
		if (find_occurence(line, j, &k, tabs[i]))
			return (1);
	}
	return (0);
}

void	fill_node_args(int *len, t_data *data, t_args *args)
{
	struct dirent	*object;
	DIR				*directory;

	directory = opendir(".");
	object = readdir(directory);
	if (directory == NULL)
		return ;
	while (object)
	{
		if ((args -> args[0] == 0 && object -> d_name[0] != '.')
			|| valid_regex(object -> d_name, args -> args) == 0)
			update_list_args(
				data, &args -> args_expands, object -> d_name, len);
		object = readdir(directory);
	}
	if (closedir(directory) < 0)
		return ;
}
