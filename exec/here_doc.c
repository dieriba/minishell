/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:46:00 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/06 12:49:12 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_here_doc_len(t_cmd **cmds)
{
	size_t	i;
	int		len;

	len = 0;
	i = -1;
	while (cmds[++i])
		len += ft_tablen(cmds[i]-> in_here_doc);	
}

void	open_here_doc(t_data *data)
{
	data -> here_doc_fds = ft_calloc(sizeof(int *), len)
}