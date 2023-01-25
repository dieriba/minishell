/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 21:08:29 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/25 13:18:32 by dtoure           ###   ########.fr       */
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
		else if (tab[i]-> type == DOC)
			file_type = "here_doc";
		printf("-------------index : %ld-------------\n", i + 1);
		printf("File_name : %s\n", tab[i]-> files);
		printf("Ambiguous redirect : %d\n", tab[i]-> amb);
		printf("File type : %s\n", file_type);
		printf("-------------index : %ld-------------\n\n", i + 1);
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
		print_files_tabs(cmds[i]-> tab, "Files Tab");
		printf("\n");
		printf("*************** Last Infile *************** \n\n");
		printf("%s\n", cmds[i]-> last_in  ? cmds[i]-> last_in -> files : "No infile");
		printf("*************** Last Outfile *************** \n\n");
		printf("%s\n", cmds[i]-> last_out ? cmds[i]-> last_out -> files : "Not oufile");
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

void	print_env(char **tab)
{
	size_t	i;

	i = -1;
	printf("*************** ENV ***************\n\n");
	while (tab[++i])
		printf("%s\n", tab[i]);
}
