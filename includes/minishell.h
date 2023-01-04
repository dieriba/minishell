/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 22:51:22 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/04 23:24:15 by dtoure           ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>

# define R_IN '<'
# define R_OUT '>'
# define R_COMBO "<>"

# define STOP	"|& "
# define STOP_	"|&"
# define STOP_F "|&<> "
# define STOP_F_P "|&<> )\"'"
# define STOP_EXP "\\'\"$&|<> "
# define VALID_COMB_EXP "\0$\" "
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
# define PIPE_INIT_ERROR "Pipe initialization  error"
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
	char	**paths;
	char	par;
	int		pos_in;
	int		pos_out;
	int		pid;
	int		pos_app;
	int		pos_here;
	int		out_redirection;
	int		in_redirection;
	char	stop[2];
	int		fd;
	int		index;
	int		no_path;
	int		p_open;
	int		p_close;
	t_data	*data;
}	t_cmd;

typedef struct t_data
{
	int					status;
	struct sigaction	ctrl_c;
	char				*path;
	char				*cp_to_parse;
	t_env				*env;
	t_node				*collector;
	t_cmd				**cmds;
	int					pipes[2];
	int					inited;
	int					prev_pipes;
	int					last_exec_stat;
	int					neg_single_start;
	int					neg_single_end;
	int					neg_double_start;
	int					neg_double_end;
}t_data;

/*-----------------GLOBAL_VARIABLE_SET-----------------*/
extern int				g_exit_prog;
/*-----------------GLOBAL_VARIABLE_SET-----------------*/

/*-----------------SIGNAL_FUNCTION-----------------*/
void	handle_signals(t_data *data);
/*-----------------SIGNAL_FUNCTION-----------------*/

/*-----------------ERROR_HANDLING-----------------*/
int		is_str_valid(t_data *data, char *to_parse);
int		check_parenthese(char *to_parse);
void	print_err_and_exit(t_data *data, t_cmd *cmd, char *err_msg, int type);
int		print_bad_syntax(t_data *data, char *str, char token);
void	check_lines(t_data *data, char *files, char *err, int flags);
/*-----------------ERROR_HANDLING-----------------*/

/*-----------------GLOBAL_UTILS-----------------*/
t_node	*create_node(t_data *data, char *line, int alloc);
t_node	*find_var(t_node *node, char *to_find);
t_node	*ft_lst_add_front_s(t_data *data, t_node **node, t_node *new);
t_node	*ft_lstlast_s(t_node *lst);
int		check_behind(char *to_parse, char *in, int j, int index);
/*-----------------GLOBAL_UTILS-----------------*/

/*-----------------DEBUG_UTILS-----------------*/
void	print_tab(char **tab, char *name);
void	print_struct(t_cmd **cmds);
void	print_env(t_node *node);
/*-----------------DEBUG_UTILS-----------------*/

/*-----------------INITIALIZATION_UTILS-----------------*/
int		skip_spaces(t_data *data, char *to_parse, int i, int skip);
int		count_words(t_data *data, char *to_parse);
int		is_same_token(char c, char d);
int		skip_char_letter_str(
			t_data *data, size_t i, char *to_parse, char *to_skip);
int		skip_char_token_str(size_t i, char *to_parse, char *to_skip);
int		check_quotes(char *to_parse, int i);
int		calcul_word(t_data *data, char *to_parse, int j);
int		find_end_string(t_data *data, char *to_parse, int j);
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
void	init_path(t_cmd **cmds);
/*-----------------INITIALIZATION-----------------*/

/*-----------------PARSER-----------------*/
int		valid_quotes(char *to_parse);
int		is_real_stop(t_data *data, char *to_parse, size_t i, char *in);
int		find_start_quotes(t_data *data, char *to_parse, int i);
int		find_end_quotes(t_data *data, char *to_parse, int i);
int		loop_nested_quote(char *to_parse, int j, int end);
int		length_of_quotes(char *to_parse, char quote);
void	quote_to_neg(t_data *data, char *to_parse);
int		char_is_quote(t_data *data, char c);
int		char_is_end_quote(t_data *data, char c);
char	*parse_double_q(t_data *data, char *to_clean);
void	parser(t_data *data, char **tab);
int		skip_next_stop(t_data *data, char *to_clean);
char	*cleaner(t_data *data, char *to_clean);
char	*is_valid_expand(t_data *data, char *to_check);
int		skip_invalid_dollars(t_data *data, char *to_parse, int j);
/*-----------------PARSER-----------------*/

/*-----------------BUILT_IN-----------------*/
void	env(t_node *node);
char	*get_var_line(t_node *node);
/*-----------------BUILT_IN-----------------*/

/*-----------------EXECUTION-----------------*/
int		prepare_next_step(t_cmd **cmd, char *stop, int i);
int		find_cmd_in_par(t_cmd **cmds, t_cmd *cmd, int i);
char	*find_lim_par(t_cmd **cmds, int p_num, int i);
void	executing(t_data *data, t_cmd **cmds);
void	run_cmd(t_cmd *cmd);
void	wait_all_child(t_data *data, t_cmd **cmds);
void	open_files(t_data *data, char **files, int length, int flags);
void	close_fd(t_data *data, char *str, int fd);
void	check_files(t_data *data, char **files, int flags);
void	close_pipes(t_data *data);
void	set_redirections_files(t_cmd *cmd, char *str);
int		opener_outfile(t_cmd *cmd, int len_out, int len_out_ap);
/*-----------------EXECUTION-----------------*/
/*-----------------FREE_STRUCT-----------------*/
void	free_list(t_env *env, t_node **head);
void	free_cmd(t_cmd **cmds);
void	free_all(t_data *data, int status);
void	clean_struct(t_data *data);
/*-----------------FREE_STRUCT-----------------*/

/*-----------------ERROR_HANDLING-----------------*/
void	is_error(t_data *data, void *elem, char *err_msg, int type);
/*-----------------ERROR_HANDLING-----------------*/

#endif