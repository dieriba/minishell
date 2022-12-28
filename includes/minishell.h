/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 22:51:22 by dtoure            #+#    #+#             */
/*   Updated: 2022/12/28 23:28:35 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "../libft/ft_printf/ft_printf.h"
# include "../libft/get_next_line/get_next_line.h"
# include <unistd.h>
# include <errno.h>
# include <stdio.h>
# include <signal.h>

# define R_IN '<'
# define R_OUT '>'
# define R_COMBO "<>"
# define STOP	"|& "
# define STOP_	"|&"
# define STOP_F "|&<> "
# define MALLOC_ERR "Sorry, no memory enough left for you."
# define ENV_ERR "Sorry, no environnement variable avaible right now."

typedef struct t_node	t_node;
typedef struct t_data	t_data;

typedef struct t_node
{
	char	*line;
	char	alloc;
	t_node	*next;
	t_node	*prev;
}	t_node;

typedef struct t_env
{
	t_node	*start;
	t_node	*last;
	t_data	*data;
}	t_env;

typedef struct t_cmd
{
	char	*cmd;
	char	**args;
	char	**in;
	char	**out;
	char	**in_here_doc;
	char	**out_append;
	char	*last_in;
	char	*last_out;
	char	stop;
	int		exec;
	int		index;
	t_data	*data;
}	t_cmd;

typedef struct t_data
{
	int		status;
	int		out_redirection;
	int		in_redirection;
	t_env	*env;
	t_cmd	**cmds;
	int		pipes[2];
}t_data;

/*-----------------GLOBAL_UTILS-----------------*/
t_node	*create_node(t_data *data, char *line, int alloc);
t_node	*find_var(t_node *node, char *to_find);
/*-----------------GLOBAL_UTILS-----------------*/

/*-----------------DEBUG_UTILS-----------------*/
void	print_tab(char **tab, char *name);
void	print_struct(t_cmd **cmds);
void	print_env(t_node *node);
/*-----------------DEBUG_UTILS-----------------*/

/*-----------------INITIALIZATION_UTILS-----------------*/
int		skip_spaces(char *to_parse, int i);
int		count_words(char *to_parse);
void	create_list(t_data *data, char **envp);
/*-----------------INITIALIZATION_UTILS-----------------*/

/*-----------------INITIALIZATION-----------------*/
void	init_cmd(t_data *data, char *to_process);
void	init_env(t_data *data, char **envp);
void	set_commands(t_cmd *cmd, char *to_parse);
void	set_redirect_cmd(t_cmd *cmd, char *to_parse, char redirect);
void	set_heredoc_app_redirect(t_cmd *cmd, char *to_parse, char *redirect);
/*-----------------INITIALIZATION-----------------*/

/*-----------------BUILT_IN_UTILS-----------------*/

/*-----------------BUILT_IN_UTILS-----------------*/

/*-----------------BUILT_IN-----------------*/
void	env(t_node *node);
/*-----------------BUILT_IN-----------------*/

/*-----------------FREE_STRUCT-----------------*/
void	free_list(t_env *env, t_node **head);
void	free_cmd(t_cmd **cmds);
void	free_all(t_data *data);
/*-----------------FREE_STRUCT-----------------*/

/*-----------------ERROR_HANDLING-----------------*/
void	is_error(t_data *data, void *elem, char *err_msg);
/*-----------------ERROR_HANDLING-----------------*/

#endif