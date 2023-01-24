/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 06:03:06 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/24 19:48:30 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_dollars(char c, char *to_clean, int i)
{
	int	valid;

	valid = 0;
	while (i > 0 && --i >= 0 && to_clean[i] > 0)
		;
	if (to_clean[i] < 0 && to_clean[i] == '\'' * -1)
		valid = -1;
	if (ft_strchr(VALID_COMB_EXP, c) || c == 0 || valid == -1)
		return (1);
	return (valid);
}
