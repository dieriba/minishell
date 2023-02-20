/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 18:30:25 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/20 16:46:24 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*is_valid_expand(t_data *data, char *to_check)
{
	char	stop;
	char	*line;
	size_t	i;
	int		j;

	j = (to_check[0] == '$');
	i = skip_next_stop(to_check);
	stop = to_check[i];
	to_check[i] = 0;
	line = get_var_line(find_var(data -> env -> tab, &to_check[j]));
	if (line == NULL)
		line = is_shell_variable(data, &to_check[j]);
	to_check[i] = stop;
	return (line);
}

size_t	get_expand_val(t_data *data, t_node **expands, char *to_clean, int skip)
{
	size_t	i;
	size_t	len;

	len = 0;
	i = -1;
	while (to_clean[++i])
	{
		if ((to_clean[i] == '"' && valid_double(to_clean, i)))
			i += handle_quote_expands(data, expands, &to_clean[i], &len);
		else if (to_clean[i] == '\'')
			while (to_clean[++i] && to_clean[i] != '\'')
				len++;
		else if (skip && to_clean[i] == '$' && !check_dollars(to_clean[i + 1]))
			i += handle_expands(data, expands, &to_clean[i], &len);
		else if (to_clean[i] == '\\')
			i = slash_len(to_clean, i, &len);
		else if ((to_clean[i] != '\'' && to_clean[i] != '"')
			|| (to_clean[i] == '"' && !valid_double(to_clean, i)))
			len++;
		if (to_clean[i] == 0)
			break ;
	}
	return (len);
}

size_t	copy_expands_in_str(char *res, char quote, t_node **node)
{
	t_node	*expands;
	size_t	j;
	int		q;

	q = 0;
	expands = (*node);
	if (!expands || expands -> line == NULL)
		return (0);
	if (quote == '"' || quote == '\'')
		q = 1;
	j = copy(expands -> line, res, q);
	if (expands -> prev)
		(*node) = expands -> prev;
	return (j);
}

void	expand_and_clean(char *to_clean, char *res, t_node *expands, int skip)
{
	size_t	i;
	size_t	j;
	t_node	*node;

	node = expands;
	i = -1;
	j = 0;
	while (to_clean[++i])
	{
		if ((to_clean[i] == '"' && valid_double(to_clean, i)))
			j += copy_expands_quote(to_clean, &res[j], &i, &node);
		else if (to_clean[i] == '\'')
			j += copy_single_quote(to_clean, &res[j], &i);
		else if (to_clean[i] == '\\')
			j += copy_slash(to_clean, &res[j], &i);
		else if (skip && to_clean[i] == '$' && !check_dollars(to_clean[i + 1]))
		{
			j += copy_expands_in_str(&res[j], to_clean[i], &node);
			i += skip_next_stop(&to_clean[i]) - 1;
		}
		else if ((to_clean[i] != '\'' && to_clean[i] != '"')
			|| (to_clean[i] == '"' && !valid_double(to_clean, i)))
			res[j++] = to_clean[i];
		if (to_clean[i] == 0)
			break ;
	}
}

char	*clean_(t_data *data, char *to_clean, int skip)
{
	t_node	*expands;
	char	*res;
	size_t	len;

	expands = NULL;
	len = get_expand_val(data, &expands, to_clean, skip);
	res = ft_calloc(sizeof(char), len + 1);
	is_error(data, res, MALLOC_ERR, 0);
	expand_and_clean(to_clean, res, ft_lstlast_s(expands), skip);
	free_list(NULL, &expands);
	ft_free_elem((void **)&to_clean);
	return (res);
}
