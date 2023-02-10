/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:42:29 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/10 02:56:22 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"
# include "stdio.h"

void	skip_split(char *to_parse, size_t *i, int quote)
{
	size_t	j;

	j = (*i);
	while (1)
	{
		while (to_parse[++j])
		{
			if ((to_parse[j] == quote && to_parse[j] == '"')
				&& valid_double_split(to_parse, j))
				break ;
			else if (to_parse[j] == quote && to_parse[j] != '"')
				break ;
		}
		if (to_parse[j + 1] == '\'' || to_parse[j + 1] == '"')
			quote = to_parse[++j];
		else
			break ;
	}
	(*i) = j;
}

int	valid_double_split(char const *s, size_t i)
{
	if ((i > 0 && s[i - 1] != '\\') || i == 0)
		return (1);
	return (0);
}

int	find_end_word(char *s, char c, size_t k)
{
	while (s[k] && s[k] != c)
	{
		if ((s[k] == '"' && valid_double_split(s, k)) || s[k] == '\'')
			skip_split(s, &k, s[k]);
		k++;
	}
	return (k);
}

int	free_all_tab_split(char **tab, int len)
{
	int	i;

	i = -1;
	while (++i < len)
		free(tab[i]);
	free(tab);
	return (1);
}