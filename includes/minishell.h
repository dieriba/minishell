/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 22:51:22 by dtoure            #+#    #+#             */
/*   Updated: 2023/01/30 16:02:17 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "../libft/ft_printf/ft_printf.h"
# include "../libft/get_next_line/get_next_line.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>

# define ALL_FLAGS 71
# define QUOTES 34
# define QUOTES_EMPT 35
# define DOLLARS_EMPT 37
# define CAPACITY 20
# define R_IN '<'
# define R_OUT '>'
# define R_COMBO "<>"
# define STOP	"|& "
# define BASE_STOP	"|&"
# define STOP_	"|&;"
# define STOP_F "|&<>; "
# define STOP_F_P "|&<> )\"'"
# define STOP_EXP "\\ '\"$&|<> ="
# define VALID_COMB_EXP "$ "
# define VALID_ ";()"
/*-----------------GLOBAL_CHECK-----------------*/
# define FORMAT_TOKEN "|&<>"
# define FORMAT_TOKEN_P "|&<>()"
# define FORMAT_TOKEN_SP "|&<>; "
# define FORMAT_TOKEN_SP_R "|&<> )"
# define FORMAT_TOKEN_SP_RR "|&<>)"
# define DELIM_TOKEN "|&<>();"
# define DELIM_TOKEN_SP "|&<>;"
# define DELIM_TOKEN_SP_G "|&<>;()"
# define MAX_LEN_TOKEN 2
# define EXCLUDE_TOKEN "{[]};"
/*-----------------GLOBAL_CHECK-----------------*/

# define MALLOC_ERR "Sorry, no memory enough left for you."
# define ENV_ERR "Sorry, no environnement variable avaible right now."
# define PIPE_INIT_ERROR "Pipe initialization  error"
# define TOKEN_SYNTAX_ERR "bash: syntax error near unexpected token : "
# define TOKEN_EOF_ERR "bash: syntax error: unexpected end of file"
# define AMB_REDIRECT "bash : ambiguous redirect"
# define MISSING_QUOTES "bash : missing end quotes"

# define LOG_FILE "log_alias"
# define ALIAS_FILENAME "populate_aliases"

enum e_type
{
	IN,
	OUT,
	DOC,
	APPEND,
};
typedef struct t_node		t_node;
typedef struct t_data		t_data;
typedef struct t_cmd		t_cmd;
typedef struct t_collector	t_collector;
typedef struct t_doc		t_doc;
typedef struct t_alias		t_alias;

typedef struct t_alias
{
	t_node	*head;
	t_node	*last;
}	t_alias;

typedef struct t_doc
{
	int		pipes[2];
	char	*limiter;
	t_doc	*next;
	t_doc	*prev;
}	t_doc;
typedef struct t_collector
{
	void		*data;
	t_collector	*next;
}	t_collector;
typedef struct t_node
{
	char	*line;
	char	alloc;
	int		i;
	t_node	*next;
	t_node	*prev;
}	t_node;
typedef struct t_env
{
	t_data	*data;
	int		capacity;
	int		len;
	char	**tab;
}	t_env;
typedef struct t_files
{
	char		*files;
	int			amb;
	int			flags;
	int			fd;
	enum e_type	type;
}	t_files;

typedef struct t_cmd
{
	char	stop[2];
	char	*cmd;
	char	*prev_stop;
	char	**args;
	char	**paths;
	int		amb_redirect;
	int		to_fork;
	int		no_path;
	int		p_close;
	int		p_open;
	int		index;
	int		pid;
	int		to_not_calloc;
	int		_close;
	int		_open;
	int		to_not_exec;
	t_files	*last_in;
	t_files	*last_out;
	t_files	**tab;
	t_data	*data;
	t_cmd	*prev_cmd;
}	t_cmd;

typedef struct t_data
{
	int					inited;
	int					status;
	int					subshell;
	int					subshell_pid;
	int					sub_pipes[2][2];
	int					s_pipes_inited;
	int					p_num;
	int					pipes[2];
	int					prev_pipes;
	int					*p_pipes;
	int					neg_single_start;
	int					neg_single_end;
	int					neg_double_start;
	int					neg_double_end;
	int					last_exec_stat;
	char				*path;
	char				*cp_to_parse;
	char				**envp;
	char				**tab_;
	struct sigaction	ctrl_c;
	t_env				*env;
	t_alias				*alias;
	t_node				*collector;
	t_cmd				**cmds;
	t_doc				*here_docs;
}t_data;

/*-----------------SYSCALL-----------------*/
void	dup_(t_data *data, int fd, int old_fd);
void	dup_and_close(t_data *data, int fd, int old_fd, int to_close);
/*-----------------SYSCALL-----------------*/

/*-----------------GLOBAL_VARIABLE_SET-----------------*/
extern t_collector			*g_collector;
/*-----------------GLOBAL_VARIABLE_SET-----------------*/

/*-----------------SIGNAL_FUNCTION-----------------*/
void	handle_signals(t_data *data);
void	new_line(int signal);
/*-----------------SIGNAL_FUNCTION-----------------*/

/*-----------------ERROR_HANDLING-----------------*/
int		is_str_valid(t_data *data, char *to_parse);
int		check_parenthese(t_data *data, char *to_parse);
int		print_bad_syntax(t_data *data, char *str, char token);
int		missing_right_commands(char *to_parse);
void	print_err_and_exit(t_data *data, t_cmd *cmd, char *err_msg, int type);
void	check_lines(t_data *data, char *files, char *err, int flags);
void	skip_reverse(char *to_parse, int *i, int quote);
void	skip_(char *to_parse, size_t *i, int quote);
/*-----------------ERROR_HANDLING-----------------*/

/*-----------------GLOBAL_UTILS-----------------*/
t_node	*create_node(t_data *data, char *line, int alloc);
t_node	*ft_lst_add_front_s(t_node **node, t_node *new);
t_node	*ft_lstlast_s(t_node *lst);
char	*find_var(char **tab, char *to_find);
/*-----------------GLOBAL_UTILS-----------------*/

/*-----------------DEBUG_UTILS-----------------*/
void	print_tab(char **tab, char *name);
void	print_struct(t_cmd **cmds);
void	print_env(char **tab);
/*-----------------DEBUG_UTILS-----------------*/

/*-----------------INITIALIZATION_UTILS-----------------*/
int		skip_spaces(t_data *data, char *to_parse, int i, int skip);
int		count_words(t_data *data, char *to_parse);
int		is_same_token(char c, char d);
int		check_condition(char *line, int j);
int		skip_char_letter_str(
			t_data *data, size_t i, char *to_parse, char *to_skip);
int		check_behind(char *to_parse, int j);
int		check_behind_par(char *to_parse, int i);
int		skip_char_token_str(size_t i, char *to_parse, char *to_skip);
int		add_command(t_data *data, char *to_process, int i);
int		check_quotes(char *to_parse, int i);
int		find_end_string(t_data *data, char *to_parse, int j);
void	create_list(t_data *data, char **envp, int len);
void	par_to_space(char *str);
void	set_parenthese(t_cmd *cmd, char *to_parse);
void	set_default_data(t_data *data, int len);
void	set_last_setup(t_cmd *cmd);
void	file_type(t_files *redirect, char a, char b);
void	init_struct(t_data **data);
void	last_node(t_data *data);
/*-----------------INITIALIZATION_UTILS-----------------*/

/*-----------------INITIALIZATION-----------------*/
void	init_cmd(t_data *data, char *to_process);
void	init_env(t_data *data, char **envp);
int		check(char *env, char *to_check);
void	set_commands(t_cmd *cmd, char *to_parse);
void	set_redirect_cmd(t_cmd *cmd, char *to_parse);
void	init_path(t_cmd *cmd);
void	real_subshell_or_not(t_cmd **cmds);
size_t	skip_redirect(t_data *data, char *to_parse, size_t i);
t_files	*copy_files(t_data *data, char *to_parse, int k, int j);
/*-----------------INITIALIZATION-----------------*/

/*-----------------PARSER-----------------*/
int		valid_quotes(t_data *data, char *to_parse);
int		valid_parentheses(char *to_parse, int *open, size_t i);
int		is_real_stop(t_data *data, char *to_parse, size_t i, char *in);
int		find_start_quotes(t_data *data, char *to_parse, int i);
int		find_end_quotes(t_data *data, char *to_parse, int i);
int		loop_nested_quote(char *to_parse, int j, int end);
int		length_of_quotes(char *to_parse, char quote);
int		check_dollars(char c, char *to_clean, int i);
int		char_is_quote(t_data *data, char c);
int		char_is_end_quote(t_data *data, char c);
int		skip_next_stop(char *to_clean);
int		skip_invalid_dollars(t_data *data, char *to_parse, int j);
int		valid_format_token(char *to_parse);
int		unvalid_line(t_data *data, char *line, char **rescue_cmd);
void	rescue_command(t_data *data, char **rescue_cmd, int err);
char	*is_shell_variable(t_data *data, char *line);
char	*cleaner(t_data *data, char *to_clean);
char	*clean_(t_data *data, char *to_clean, int skip);
char	*is_valid_expand(t_data *data, char *to_check);
void	parser(t_data *data, char **tab, int type);
void	quote_to_neg(t_data *data, char *to_parse);
char	*clean_lines(t_data *data, char *line, int expand);
void	clean_cmd(t_cmd *cmd);
void	skip_reverse(char *to_parse, int *i, int quote);
void	clean_files(t_cmd *cmd);
size_t	next_quotes(t_data *data, char *to_clean, size_t *len);
/*-----------------PARSER-----------------*/

/*-----------------BUILT_IN-----------------*/
char	*get_var_line(char *line);
char	*find_alias_node(t_data *data, char *line);
int		where_to_write(t_data *data, t_cmd *cmd, int subshell);
int		is_not_built_in(char *cmd);
int		check_line(char *line);
int		log_files_alias(char *alias, int err_code, int line);
void	export(t_cmd *cmd, t_env *env, int fork, int subshell);
void	env(t_data *data, t_cmd *cmd, int subshell, int fork);
void	unset(t_cmd *cmd, t_env *env);
void	echo(t_data *data, t_cmd *cmd, int subshell, int fork);
void	built_in(t_data *data, t_cmd *cmd, int subshell, int fork);
void	make_export(t_env *env, char *line);
void	alias(t_data *data, t_cmd *cmd, int subshell, int fork);
void	alias_(t_data *data, t_cmd *cmd, char *line, int subshell);
void	unalias(t_cmd *cmd);
void	pwd(t_data *data, t_cmd *cmd, int subshell, int fork);
void	back_to_space(char **tab);
void	populate(t_data *data, char *file);
int		populate_alias(char *line);
void	from_alias_to_hero(t_data *data, t_cmd *cmd, char **tab);
char	*from_tab_to_line(t_cmd *cmd, char **tab);
t_node	*find_(t_data *data, char *line);
void	print_alias(t_data *data, t_cmd *cmd, int subshell);
void	close_all(t_data *data, t_cmd *cmd, int subshell);
void	skip_(char *to_parse, size_t *i, int quote);
void	exit_process(t_data *data, t_cmd *cmd, int subshell, int fork);
/*-----------------BUILT_IN-----------------*/

/*-----------------EXECUTION-----------------*/
int		prepare_next_step(t_data *data, t_cmd **cmd, char *stop, int *i);
int		opener_outfile(t_cmd *cmd);
int		to_exec_or_not(char *stop, int status);
int		pipe_par(t_cmd **cmds);
int		find_next_cmd(t_data *data, t_cmd **cmds);
int		is_subshell(t_data *data, t_cmd **cmds, int *i, int subshell);
void	executing(t_data *data, t_cmd **cmds, int subshell);
void	run_cmd(t_cmd *cmd);
void	wait_all_child(t_data *data, t_cmd **cmds, int subshell);
void	open_check_files(t_cmd *cmd, t_files **tab);
void	close_fd(t_data *data, char *str, int *fd);
void	check_files(t_data *data, t_files **files, int flags);
void	close_pipes(t_data *data);
void	handle_pipes(t_data *data, t_cmd *cmd, int subshell);
void	close_both_pipes(t_data *data, int pipes[2], int *inited);
void	open_here_doc(t_data *data, t_cmd **cmds);
void	set_redirections_files(t_cmd *cmd, char *str, int subshell);
void	init_pipes(t_data *data, int pipes[2], int *inited, int s_pipes);
void	close_one_end(t_data *data, int *pipes, int i, int *inited);
void	close_sub_pipes(t_data *data, int subshell);
/*-----------------EXECUTION-----------------*/

/*-----------------PARENTHESES-----------------*/
int		end_cmd_par(t_cmd **cmds, int subshell);
/*-----------------PARENTHESES-----------------*/
/*-----------------FREE_STRUCT-----------------*/
void	free_list(t_env *env, t_node **head);
void	free_cmd(t_cmd **cmds);
void	free_all(t_data *data, int status);
void	clean_struct(t_data *data);
/*-----------------FREE_STRUCT-----------------*/

/*-----------------ERROR_HANDLING-----------------*/
void	is_error(t_data *data, void *elem, char *err_msg, int type);
/*-----------------ERROR_HANDLING-----------------*/

/*-----------------HERE_DOC_UTILS-----------------*/
int		tab_len(t_cmd **cmds);
int		find_fd(t_doc *node, char *limiter);
int		open_pipes(t_data *data, t_doc **head);
void	fork_docs(t_data *data, t_doc **head);
void	ft_lst_add_front_(t_doc **node, t_doc *new);
void	set_node(t_data *data, t_files **tab);
void	close_all_pipes(t_data *data, t_doc **head, int read_, int write_);
void	exit_(int signal);
void	clean_here_doc(t_data *data, t_doc **head);
/*-----------------HERE_DOC_UTILS-----------------*/
#endif
