/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 22:43:33 by dtoure            #+#    #+#             */
/*   Updated: 2022/12/28 08:19:18 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	how_many_cmds(char *to_process)
{
	size_t	i;
	size_t	count;

	
	i = -1;
	count = 0;
	while (to_process[++i])
	{
		if (ft_strchr(STOP_, to_process[i]))
			count++;
	}
	count++;
	return (count);
}

void	fill_cmds(t_cmd **cmds, char *to_parse, int length)
{
	int		i;
	size_t	j;

	j = 0;
	i = -1;
	while (++i < length)
	{
		set_redirect_cmd(cmds[i], &to_parse[j], '<');
		set_redirect_cmd(cmds[i], &to_parse[j], '>');
		set_commands(cmds[i], &to_parse[j]);
		while (to_parse[++j] && !ft_strchr(STOP_, to_parse[j]))
			;
		j++;
	}
}

void	print_tab(char **tab)
{
	size_t	i;

	i = -1;
	if (!tab)
	{
		printf("No args\n");
		return ;
	}
	while (tab[++i])
		printf("%s ", tab[i]);
}

void	print_struct(t_cmd **cmds)
{
	int	i;
	
	i = -1;
	while (cmds[++i])
	{
		printf("Commande Numéro : %d\n", i + 1);
		printf("Commande : %s\n", cmds[i] -> cmd);
		printf("Commande Args : \n");
		print_tab(cmds[i] -> args);
		printf("\nInfile : \n");
		print_tab(cmds[i] -> in);
		printf("\nOutfile : \n");
		print_tab(cmds[i] -> out);
		if (cmds[i] -> stop == 0)
			printf("\nPas de symbole donc seule commande \n");
		else
			printf("\nSymbole :%c \n", cmds[i] -> stop);
		if (cmds[i + 1])
			printf("\n");
	}
}

void	init_cmd(t_data *data, char *to_process)
{
	size_t	i;
	size_t	j;

	j = -1;
	i = how_many_cmds(to_process);
	data -> cmd = ft_calloc(sizeof(t_cmd *), i + 1);
	//if (!data -> cmd)
		//exit function;
	while (++j < i)
	{
		data -> cmd[j] = ft_calloc(sizeof(t_cmd), 1);
		//if (!data -> cmd[i])
			//exit funct;
	}
	fill_cmds(data -> cmd, to_process, i);
	print_struct(data -> cmd);
}