/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 22:51:22 by dtoure            #+#    #+#             */
/*   Updated: 2022/12/30 17:46:00 by dtoure           ###   ########.fr       */
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
# define STOP_F_P "|&<> )"

/*-----------------GLOBAL_CHECK-----------------*/
# define FORMAT_TOKEN "|&<>"
# define FORMAT_TOKEN_P "|&<>()"
# define FORMAT_TOKEN_SP "|&<> \0"
# define FORMAT_TOKEN_SP_R "|&<> \0)"
# define MAX_LEN_TOKEN 2
# define EXCLUDE_TOKEN "{[]};"
/*-----------------GLOBAL_CHECK-----------------*/

# define MALLOC_ERR "Sorry, no memory enough left for you."
# define ENV_ERR "Sorry, no environnement variable avaible right now."

# define TOKEN_SYNTAX_ERR "bash: syntax error near unexpected token : "

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
	char	*sub_commands;
	char	par;
	int		pos_in;
	int		pos_out;
	int		pos_app;
	int		pos_here;
	int		out_redirection;
	int		in_redirection;
	char	stop[2];
	int		index;
	int		p_open;
	int		p_close;
	t_data	*data;
}	t_cmd;

typedef struct t_data
{
	int		status;
	char	*cp_to_parse;
	t_env	*env;
	t_cmd	**cmds;
	int		pipes[2];
}t_data;

/*-----------------ERROR_HANDLING-----------------*/
int		is_str_valid(t_data *data, char *to_parse);
int		check_parenthese(char *to_parse);
int		print_bad_syntax(t_data *data, char *str, char token);
/*-----------------ERROR_HANDLING-----------------*/


/*-----------------GLOBAL_UTILS-----------------*/
t_node	*create_node(t_data *data, char *line, int alloc);
t_node	*find_var(t_node *node, char *to_find);
t_node	*ft_lst_add_front_s(t_data *data, t_node **node, t_node *new);
int		check_behind(char *to_parse, char *in, int j, int index);
/*-----------------GLOBAL_UTILS-----------------*/

/*-----------------DEBUG_UTILS-----------------*/
void	print_tab(char **tab, char *name);
void	print_struct(t_cmd **cmds);
void	print_env(t_node *node);
/*-----------------DEBUG_UTILS-----------------*/

/*-----------------INITIALIZATION_UTILS-----------------*/
int		skip_spaces(char *to_parse, int i);
int		count_words(char *to_parse);
int		is_same_token(char c, char d);
int		skip_char_in_str(size_t i, char *to_parse, char *to_skip, int opt);
void	create_list(t_data *data, char **envp);
void	par_to_space(char *str);
void	set_parenthese(t_cmd *cmd, char *to_parse);
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