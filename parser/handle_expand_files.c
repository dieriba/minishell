/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expand_files.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 03:40:35 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/20 16:29:33 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	set_pos_tab_star(t_star *tab, char *args)
{
	size_t	i;

	i = -1;
	if (args[0] == '*')
		tab -> st_bfore = 1;
	while (args[++i] && args[i] == '*')
		;
	while (args[i])
	{
		if ((args[i] == '"' && valid_double(args, i))
			|| args[i] == '\'')
			skip_(args, &i, args[i]);
		else if (args[i] == '*')
			break ;
		if (args[i] == 0)
			break ;
		i++;
	}
	tab -> st_after = (args[i] == '*');
	return (i);
}

t_star	**find_pattern(t_data *data, char *args, char ***tab_arg)
{
	char	**tabs;
	int		j;
	int		i;
	t_star	**star_tabs;

	i = -1;
	j = 0;
	tabs = ft_split(args, '*');
	is_error(data, tabs, MALLOC_ERR, 0);
	star_tabs = ft_calloc(sizeof(t_star *), ft_tab_len(tabs) + 1);
	is_error(data, star_tabs, MALLOC_ERR, 0);
	while (tabs[++i])
	{
		star_tabs[i] = ft_calloc(sizeof(t_star), 1);
		is_error(data, star_tabs[i], MALLOC_ERR, 0);
		if (i == 0)
			star_tabs[i]-> first = 1;
		else if (tabs[i + 1] == 0)
			star_tabs[i]-> last = 1;
		star_tabs[i]-> pattern = tabs[i];
		j += set_pos_tab_star(star_tabs[i], &args[j]);
	}
	(*tab_arg) = tabs;
	return (star_tabs);
}

int	set_args_(t_data *data, t_args *args, char **cmd_args)
{
	int		i;
	char	**tabs_arg;
	int		len;
	int		found;

	i = -1;
	len = 0;
	found = 0;
	while (cmd_args[++i])
	{
		if (glob_args(data, &cmd_args[i], 0, 0))
		{
			cmd_args[i] = clean_lines(data, cmd_args[i], 2);
			args -> args = find_pattern(data, cmd_args[i], &tabs_arg);
			found = fill_node_args(&len, data, args);
			if (len < 0)
				break ;
			free_tabs_args(args -> args);
			tabs_arg = ft_free_tab(tabs_arg);
			if (found)
				continue ;
		}
		update_list_args(data, &args -> args_expands, cmd_args[i], &len);
	}
	return (len);
}

void	new_expanded_tab(t_cmd *cmd, t_node **args_expands, int len)
{
	char	**tab;
	int		i;
	t_node	*node;

	i = -1;
	node = ft_lstlast_s((*args_expands));
	tab = ft_calloc(sizeof(char *), len + 1);
	is_error(cmd -> data, tab, MALLOC_ERR, 0);
	while (node)
	{
		tab[++i] = node -> line;
		node -> line = NULL;
		node = node -> prev;
	}
	if (cmd -> cmd != cmd -> args[0])
		ft_free_elem((void **)&cmd -> cmd);
	cmd -> args = ft_free_tab(cmd -> args);
	cmd -> args = tab;
	cmd -> cmd = cmd -> args[0];
	free_list(NULL, args_expands);
}

void	expand_args(t_data *data, t_cmd *cmd)
{
	int		len;
	char	*directory;
	t_args	args;

	directory = getcwd(NULL, 0);
	if (directory == NULL)
		return ;
	ft_free_elem((void **)&directory);
	args.args_expands = NULL;
	len = set_args_(data, &args, cmd -> args);
	if (len > 1)
		new_expanded_tab(cmd, &args.args_expands, len);
	else if (args.args_expands)
		free_list(NULL, &args.args_expands);
	free_list(NULL, &args.args_expands);
}
