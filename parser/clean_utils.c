/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 04:25:17 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/14 04:26:15 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*clean_lines(t_data *data, char *line, int expand)
{
	size_t	i;

	i = -1;
	if (line == NULL)
		return (line);
	while (line[++i])
	{
		if (expand && (line[i] == '$' || line[i] == '\\'))
			return (clean_(data, line, 1));
		if (expand == 0 && ((line[i] == '"' && valid_double(line, i))
				|| (line[i] == '\'' || line[i] == '\\')))
			return (clean_(data, line, 0));
	}
	return (line);
}

size_t	handle_expands(
	t_data *data, t_node **expands, char *to_clean, size_t *len)
{
	char	*line;
	char	quote;
	t_node	*node;
	size_t	i;
	size_t	j;

	j = -1;
	line = is_valid_expand(data, to_clean);
	while (line && line[++j])
	{
		if ((line[j] == '"' && valid_double(line, j)) || line[j] == '\'')
		{
			quote = line[j];
			while (line[++j] && line[j] != quote)
				(*len) += 1;
		}
		else
			(*len) += 1;
		j -= (line[j] == 0);
	}
	node = create_node(data, line, (line != NULL));
	is_error(data, node, MALLOC_ERR, 0);
	ft_lst_add_front_s(expands, node);
	i = skip_next_stop(to_clean) - 1;
	return (i);
}

size_t	handle_quote_expands(
	t_data *data, t_node **expands, char *to_clean, size_t *len)
{
	size_t	i;

	i = 0;
	while (to_clean[++i])
	{
		if (to_clean[i] == '$')
			i += handle_expands(data, expands, &to_clean[i], len);
		else if (to_clean[i] != '"')
			(*len) += 1;
		else if (to_clean[i] == '"' && !valid_double(to_clean, i))
			(*len) += 1;
		else if ((to_clean[i] == '"'
				&& valid_double(to_clean, i)) && to_clean[i + 1] != '"')
			break ;
	}
	return (i);
}

size_t	copy_expands_quote(
	char *to_clean, char *res, size_t *v, t_node **expands)
{
	size_t	i;
	size_t	j;

	i = (*v);
	j = 0;
	while (to_clean[++i])
	{
		if (to_clean[i] == '"'
			&& valid_double(to_clean, i) && to_clean[i + 1] == '"')
			i++;
		else if (to_clean[i] == '"' && valid_double(to_clean, i))
			break ;
		else if (to_clean[i] == '$')
		{
			j += copy_expands_in_str(&res[j], to_clean[(*v)], expands);
			i += skip_next_stop(&to_clean[i]) - 1;
		}
		else
			res[j++] = to_clean[i];
	}
	(*v) = i;
	return (j);
}

size_t	copy_single_quote(char *to_clean, char *res, size_t *v)
{
	size_t	i;
	size_t	j;

	i = (*v);
	j = 0;
	while (to_clean[++i])
	{
		if (to_clean[i] == '\'')
			break ;
		else if (ft_isspace(to_clean[i]))
			res[j++] = to_clean[i] * -1;
		else if (to_clean[i] != '\'')
			res[j++] = to_clean[i];
	}
	(*v) = i;
	return (j);
}
