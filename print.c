/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 21:08:29 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/23 14:14:15 by dtoure           ###   ########.fr       */
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

void	print_files_tabs(t_files **tab, char *name)
{
	size_t	i;
	char	*file_type;
	
	i = -1;
	if (!tab)
	{
		printf("Tab %s is empty\n", name);
		return ;
	}
	printf("-------------%s START-------------\n", name);
	while (tab[++i])
	{
		file_type = "infile";
		if (tab[i]-> type == OUT)
			file_type = "outfile";
		else if (tab[i]-> type == APPEND)
			file_type = "append";
		else if (tab[i]-> doc == DOC)
			file_type = "here_doc";
		printf("index : %ld file_name : %s amb value : %d type : %d\n", i + 1, tab[i]-> files, tab[i]-> amb, file_type);
	}
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
		print_tab(cmds[i]-> paths, "Possible commands paths");
		printf("\n");
		print_files_tabs(cmds[i]-> in, "Infile Tab");
		printf("\n");
		print_files_tabs(cmds[i]-> out, "Outfile Tab");
		printf("\n");
		print_files_tabs(cmds[i]-> in_here_doc, "Here_docs Tab");
		printf("\n");
		print_files_tabs(cmds[i]-> out_append, "Out append Tab");
		printf("*************** Last Infile *************** \n\n");
		printf("%s\n", cmds[i]-> last_in ? cmds[i]-> last_in : "No infile");
		printf("*************** Last Outfile *************** \n\n");
		printf("%s\n", cmds[i]-> last_out ? cmds[i]-> last_out : "Not oufile");
		printf("\n***************************************\n\n\n");
		printf("*************** PREV STOP TOKEN *************** \n\n");
		printf("%s\n", i ? cmds[i]-> prev_stop : "No stop");
		printf("*************** STOP TOKEN *************** \n\n");
		printf("%s\n", cmds[i]-> stop);
		printf("*************** OPENING PARENTHESES *************** \n\n");
		printf("%d\n", cmds[i]-> p_open);
		printf("*************** CLOSING PARENTHESES *************** \n\n");
		printf("%d\n", cmds[i]-> p_close);
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
