/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:13:26 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/18 19:25:53 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_free_tab(char **tab)
{
	size_t	i;

	if (!tab)
		return (NULL);
	i = -1;
	while (tab[++i])
		ft_free_elem((void **)&tab[i]);
	free(tab);
	return (NULL);
}
