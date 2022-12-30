/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 21:08:29 by dtoure            #+#    #+#             */
/*   Updated: 2022/12/30 03:09:03 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	print_tab(char **tab, char *name)
{
	size_t	i;

	i = -1;
	if (!tab)
	{
		printf("Tab %s is empty\n", name);
		return ;
	}
	printf("-------------%s START-------------\n", name);
	while (tab[++i])
		printf("index : %ld value : %s\n", i + 1, tab[i]);
	printf("-------------%s END -------------\n", name);
}

void	print_struct(t_cmd **cmds)
{
	int	i;

	i = -1;
	printf("\n\n");
	while (cmds[++i])
	{
		printf("*************** Command : %d ***************\n\n", i + 1);
		printf("Main Command : %s\n", cmds[i]-> cmd);
		printf("\n");
		print_tab(cmds[i]-> args, "Commands Args Tab");
		printf("\n");
		print_tab(cmds[i]-> in, "Infile Tab");
		printf("\n");
		print_tab(cmds[i]-> out, "Outfile Tab");
		printf("\n");
		print_tab(cmds[i]-> in_here_doc, "Here_docs Tab");
		printf("\n");
		print_tab(cmds[i]-> out_append, "Out append Tab");
		printf("*************** Last Infile *************** \n\n");
		printf("%s\n", cmds[i] -> last_in ? cmds[i] -> last_in : "No infile");
		printf("*************** Last Outfile *************** \n\n");
		printf("%s\n", cmds[i] -> last_out ? cmds[i] -> last_out : "Not oufile");
		printf("\n***************************************\n\n\n");
		printf("*************** STOP TOKEN *************** \n\n");
		printf("%s\n", cmds[i]-> stop);
	}
}

void	print_env(t_node *node)
{
	printf("*************** ENV ***************\n\n");
	while (node)
	{
		printf("%s\n", node -> line);
		node = node -> next;
	}
}
