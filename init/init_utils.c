/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:52:55 by dtoure            #+#    #+#             */
/*   Updated: 2022/12/29 04:41:06 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	skip_spaces(char *to_parse, int i)
{
	while (to_parse[i] && to_parse[i] == ' ')
		i++;
	return (i);
}

int	count_words(int index, char *to_parse)
{
	size_t	i;
	int		length;

	i = -1;
	length = 0;
	while (to_parse[++i])
	{
		while (to_parse[i] && to_parse[i] == ' ')
			i++;
		while (ft_strchr(R_COMBO, to_parse[i]))
			i++;
		while (to_parse[i] && to_parse[i] == ' ')
			i++;
		while (to_parse[i] && !ft_strchr(STOP_F, to_parse[i]))
			i++;
		length++;
		if (ft_strchr(STOP_, to_parse[i]) || !to_parse[i])
			break ;
	}
	if (index == 4)
		printf("Length : %d\n", length);
	if (ft_strchr(STOP_, to_parse[i]) && to_parse[i - 1] == ' ')
		--length;
	return (length);
}
