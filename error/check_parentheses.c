/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parentheses.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 14:25:28 by dtoure            #+#    #+#             */
/*   Updated: 2022/12/30 03:39:12 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*int count_parenthses(char *to_parse, char find, char to_chase)
{
    size_t  i;
    int     j;

    i = -1;
    j = 0;
    while (to_parse[++i] != to_chase)
    {
        if (to_parse[i] == find)
            j++;
    }
    return (j);
}

int check_condition(char *to_parse, int *letter, size_t i)
{
    int p_open;

    p_open = count_parenthses;
    while (to_parse[i] != ')')
    {
        if (to_parse[i] == '(')
            p_open += 1;
        i++;
    }
    
    return (i);
}

int check_empty_parentheses(char *to_parse)
{
    size_t  i;
    int     p_close;
    int     letter;
    
    p_close = 0;
    i = -1;
    while (to_parse[++i])
    {
        if (to_parse[i] == '(')
        {
            
        }
    }
    return (0);
}
*/

int valid_parentheses(char *to_parse)
{
    size_t  i;
    int     p_open;
    
    i = -1;
    p_open = 0;
    while(to_parse[++i])
    {
        if (to_parse[i] == '(')
            p_open++;
        else if (to_parse [i] == ')')
        {
            p_open--;
            if (p_open < 0)
                return (')');
        }
    }
    if (p_open)
        return (')');
    return (0);
}