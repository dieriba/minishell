/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parentheses.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 14:25:28 by dtoure            #+#    #+#             */
/*   Updated: 2022/12/29 16:10:22 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int count_parenthses(char *to_parse, char find, char to_chase)
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

int remove_node(t_node **head)
{
    t_node  *new_head;
    
    if (!(*head))
        return (1);
    new_head = (*head) -> next;
    (*head) -> next = NULL;
    free((*head));
    if (!new_head)
        (*head) = NULL;
    else
    {
        (*head) = new_head;
        (*head) -> prev = NULL;
    }
    return (0);
}

int valid_parentheses(t_data *data, char *to_parse)
{
    size_t  i;
    t_node  *head;
    t_node  *node;
    
    i = -1;
    head = NULL;
    while(to_parse[++i])
    {
        if (to_parse[i] == '(')
        {
            node = create_node(data, 0, '(');
            is_error(data, node, MALLOC_ERR);
            ft_lst_add_front_s(NULL, &head, node);
        }
        else if (to_parse[i] == ')')
        {
            if (remove_node(&head))
                return (')');
        }
    }
    if (!(head))
        return (0);
    else
        free_list(NULL, &head);
    return (')');
}