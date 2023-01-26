/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_cleaner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 02:13:18 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/26 20:31:55 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	clean_(char *to_clean, size_t stop)
{
	size_t	i;

	if (ft_strchr(VALID_COMB_EXP, to_clean[1]) || to_clean[1] == 0)
		return ;
	i = -1;
	while (++i < stop)
		to_clean[i] = ' ';
}