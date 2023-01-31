/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:12:39 by dtoure            #+#    #+#             */
/*   Updated: 2022/11/08 14:12:39 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2, char const *s3)
{
	size_t	i;
	size_t	j;
    size_t  k;
	char	*buff;

	if (!s2)
		return (NULL);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
    k = ft_strlen(s3);
	buff = calloc(sizeof(char), (i + j + k + 1));
	if (!buff)
		return (NULL);
	ft_memcpy(buff, s1, i);
    if (s3)
		ft_memcpy(buff + i, s3, k);
	ft_memcpy(buff + i + k, s2, (j + 1));
	return (buff);
}
