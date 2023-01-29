/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bad_syntax_alias_files.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 00:17:41 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/29 02:09:49 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	log_files_alias(char *alias, int err_code, int line)
{
	static char	*start_ = "Could not create the alias, ";
	static char	*middle_ = "because of an error occured at line : ";
	int			err;

	err = 0;
	err = ft_printf("%s%s%d", start_, middle_, line);
	if (err >= 0 && err_code == -1)
		err = ft_printf(" %s does not contains '='\n", alias);
	else if (err >= 0 && err_code == -2)
		err = ft_printf(" %s has no charactes before first equal\n", alias);
	else if (err >= 0 && err_code == -3)
		err = ft_printf(" %s contains invalid characters before '='\n", alias);
	if (err < 0)
		return (-4);
	return (0);
}
