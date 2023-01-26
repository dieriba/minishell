/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 18:30:25 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/26 21:51:38 by dtoure           ###   ########.fr       */
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
	t_node	*node;
	char	*line;
	size_t	len;

	len = 0;
	i = -1;
	while (to_clean[++i])
	{
		if (skip && to_clean[i] == '$' && !check_dollars(to_clean[i + 1], to_clean, i))
		{
			line = is_valid_expand(data, &to_clean[i]);
			len += ft_strlen(line);
			node = create_node(data, line, (line != NULL));
			is_error(data, node, MALLOC_ERR, 0);
			ft_lst_add_front_s(expands, node);
			i += skip_next_stop(&to_clean[i]);
			i--;
		}
		else if (to_clean[i] > 0 || ((to_clean[i] * -1) == ' '))
			len++;
	}
	return (len);
}

size_t	copy_expands_in_str(char *res, char *to_clean, t_node *expands)
{
	size_t	i;
	size_t	j;

	if (!expands || expands -> line == NULL)
		return (0);
	j = -1;
	i = -1;
	while (to_clean[++j] && (to_clean[j] > 0 || to_clean[j] == ' ' * -1))
		;
	while (expands -> line[++i])
	{
		if (to_clean[j] == '"' * -2 && expands -> line[i] == ' ')
			res[i] = expands -> line[i] * -1;
		else
			res[i] = expands -> line[i];
	}
	return (i);
}

char	*expand_and_clean(char *to_clean, char *res, t_node *expands, int skip)
{
	size_t	i;
	size_t	j;
	
	j = 0;
	i = -1;
	while (to_clean[++i])
	{
		if (skip && to_clean[i] == '$' && !check_dollars(to_clean[i + 1], to_clean, i))
		{
			j += copy_expands_in_str(&res[j], &to_clean[i], expands);
			i += skip_next_stop(&to_clean[i]);
			if (expands -> prev)
				expands = expands -> prev;
			i--;
		}
		else if (to_clean[i] > 0 || ((to_clean[i] * -1) == ' '))
			res[j++] = to_clean[i];
	}
	return (res);
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
	free(to_clean);
	return (res);
}
