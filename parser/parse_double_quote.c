/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_double_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 18:30:25 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/03 23:01:33 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*is_valid_expand(t_data *data, char *to_check)
{
	char	stop;
	char	*line;
	size_t	i;

	i = skip_next_stop(to_check);
	stop = to_check[i];
	to_check[i] = 0;
	line = get_var_line(find_var(data -> env -> start, &to_check[0]));
	to_check[i] = stop;
	return (line);
}

size_t	get_expand_val(t_data *data, t_node **expands, char *to_clean)
{
	size_t	i;
	t_node	*node;
	char	*line;
	size_t	len;

	len = 0;
	i = -1;
	while (to_clean[++i])
	{
		if (to_clean[i] == '$')
		{
			line = is_valid_expand(data, &to_clean[++i]);
			len += ft_strlen(line);
			node = create_node(data, line, (line != NULL));
			is_error(data, node, MALLOC_ERR, 0);
			ft_lst_add_front_s(data, expands, node);
			i += skip_next_stop(&to_clean[i]);
		}
		if (to_clean[i] > 0 && to_clean[i] != '$')
			len++;
		i -= (to_clean[i] == '$');
		i -= (to_clean[i] == '\0');
	}
	return (len);
}

size_t	copy_expands_in_str(char *res, t_node *expands)
{
	size_t	i;

	if (!expands || expands -> line == NULL)
		return (0);
	printf("entered\n");
	i = -1;
	while (expands -> line[++i])
		res[i] = expands -> line[i];
	return (i);
}

char	*expand_and_clean(
	t_data *data, char *to_clean, t_node *expands, size_t len)
{
	size_t	i;
	size_t	j;
	char	*res;

	res = ft_calloc(sizeof(char), len + 1);
	is_error(data, res, MALLOC_ERR, 0);
	j = 0;
	i = -1;
	while (to_clean[++i])
	{
		if (to_clean[i] == '$')
		{
			j += copy_expands_in_str(&res[j], expands);
			i += skip_next_stop(&to_clean[i]);
			printf("i val :  %ld\n", i);
			if (expands -> prev)
				expands = expands -> prev;
		}
		if (to_clean[i] > 0 && to_clean[i] != '$')
			res[j++] = to_clean[i];
		i -= (to_clean[i] == '$');
		i -= (to_clean[i] == '\0');
	}
	return (res);
}

char	*parse_double_q(t_data *data, char *to_clean)
{
	t_node	*expands;
	char	*res;
	size_t	len;

	expands = NULL;
	len = get_expand_val(data, &expands, to_clean);
	expands = ft_lstlast_s(expands);
	res = expand_and_clean(data, to_clean, expands, len);
	free(to_clean);
	return (res);
}
