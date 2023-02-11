/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 22:51:22 by dtoure            #+#    #+#             */
/*   Updated: 2023/02/11 18:44:12 by dtoure           ###   ########.fr       */
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
# include <dirent.h>
/*-----------------COLOR_-----------------*/
# define CYAN "\001\033[0;36m\002"
# define RESET_COLOR "\001\033[0m\002"
# define RED "\001\033[0;31m\002"
# define GREEN "\001\033[0;32m\002"
/*-----------------COLOR_-----------------*/
# define ALL_FLAGS 71
# define QUOTES 34
# define QUOTES_EMPT 35
# define DOLLARS_EMPT 37
# define CAPACITY 20
# define R_IN '<'
# define R_OUT '>'
# define R_COMBO "<>"
# define R_COMBO_DOLLARS "<>$"
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
# define ALIAS_AUTHORIZED "._!-"
/*-----------------GLOBAL_CHECK-----------------*/

# define MALLOC_ERR "Sorry, no enough memory left for you."
# define ENV_ERR "Sorry, no environnement variable avaible right now."
# define PIPE_INIT_ERROR "Pipe initialization  error"
# define TOKEN_SYNTAX_ERR "bash: syntax error near unexpected token : "
# define TOKEN_EOF_ERR "bash: syntax error: unexpected end of file"
# define AMB_REDIRECT "bash : ambiguous redirect"
# define MISSING_QUOTES "bash : missing end quotes"
# define GET_CWD_ERR "getcwd: cannot access parent directories"
# define PWD_ERROR "pwd: error retrieving current directory: "
# define CHDIR_ERROR "chdir: error retrieving current directory: "
# define LOG_FILE "log_alias"
# define ALIAS_FILENAME "populate_aliases"
# define EXIT_ARGS "bash : exit: too many arguments"
# define EXIT_NUM_ARGS "bash: exit: numeric argument required"

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
typedef struct t_pipes		t_pipes;
typedef struct t_s_pipes	t_s_pipes;

typedef struct t_dir
{
	char	*path;
	char	*dir_name;
	char	*pwd;
	int		new_dir;
}	t_dir;

typedef struct t_alias
{
	t_node	*head;
	t_node	*last;
}	t_alias;
typedef struct t_s_pipes
{
	int			s_pipes[2];
	pid_t		pid;
	t_s_pipes	*next;
}	t_s_pipes;
typedef struct t_doc
{
	int		pipes[2];
	char	*limiter;
	int		quoted;
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
	char		stop[2];
	char		*cmd;
	char		*prev_stop;
	char		**args;
	char		**paths;
	int			amb_redirect;
	int			to_fork;
	int			no_path;
	int			p_close;
	int			p_open;
	int			pid;
	int			to_not_calloc;
	int			_close;
	int			_open;
	int			to_not_exec;
	int			built_in;
	int			break_cmd;
	int			executed;
	int			exit_status;
	t_s_pipes	*write_end;
	t_s_pipes	*read_end;
	t_files		*last_in;
	t_files		*last_out;
	t_files		**tab;
	t_data		*data;
	t_cmd		*prev_cmd;
}	t_cmd;

typedef struct t_data
{
	int					inited;
	int					status;
	int					subshell;
	int					subshell_pid;
	int					pipes[2];
	int					prev_pipes;
	int					last_exec_stat;
	char				*path;
	char				*cp_to_parse;
	char				**envp;
	char				**tab_;
	t_s_pipes			*s_pipes;
	t_dir				curr_dir;
	t_env				*env;
	t_alias				*alias;
	t_node				*collector;
	t_cmd				**cmds;
	t_doc				*here_docs;
}t_data;

/*-----------------SYSCALL-----------------*/
void	dup_and_close(t_data *data, int fd, int old_fd, int to_close);
int		dup_and_close_built_in(int fd, int old_fd);
/*-----------------SYSCALL-----------------*/
/*-----------------MINISHELL-----------------*/
void	lets_read(t_data *data);
void	shell_routine(t_data *data);
/*-----------------MINISHEL-----------------*/

/*-----------------GLOBAL_VARIABLE_SET-----------------*/
extern t_collector			*g_collector;
/*-----------------GLOBAL_VARIABLE_SET-----------------*/

/*-----------------SIGNAL_FUNCTION-----------------*/
void	handle_signals(void);
void	ignore_signals(void);
void	new_line(int signal);
void	sig_int_fork(int signal);
/*-----------------SIGNAL_FUNCTION-----------------*/

/*-----------------ERROR_HANDLING-----------------*/
int		print_bad_syntax(t_data *data, char *str, char token);
int		check_token_length(char *to_parse);
int		check_in_front(char *to_parse, int token, size_t *j);
int		valid_double(char *to_parse, size_t i);
int		check_function(char *to_parse, size_t i);
void	print_err_and_exit(t_data *data, t_cmd *cmd, char *err_msg, int type);
void	skip_reverse(char *to_parse, int *i, int quote);
void	skip_(char *to_parse, size_t *i, int quote);
void	exit_dumped(int signal);
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
int		skip_spaces(char *to_parse, int i, int skip);
int		count_words(char *to_parse);
int		is_same_token(char c, char d);
int		check_condition(char *line, int j);
int		skip_char_letter_str(char *to_parse, size_t i);
int		check_behind(char *to_parse, int j);
int		check_behind_par(char *to_parse, int i);
int		skip_char_token_str(char *to_parse, char *to_skip, size_t i);
int		add_command(char *to_process, int i);
int		check_quotes(char *to_parse, int i);
void	directory(t_data *data);
void	set_parenthese(t_cmd *cmd, char *to_parse);
void	set_default_data(t_data *data, int len);
void	set_last_setup(t_cmd *cmd);
void	file_type(t_files *redirect, char a, char b);
void	init_struct(t_data **data);
void	last_node(t_data *data);
void	par_to_space(char *to_clean);
/*-----------------INITIALIZATION_UTILS-----------------*/

/*-----------------INITIALIZATION-----------------*/
void	init_cmd(t_data *data, char *to_process);
void	init_env(t_data *data, char **envp);
int		check(char *env, char *to_check);
void	set_commands(t_cmd *cmd, char *to_parse);
void	set_redirect_cmd(t_cmd *cmd, char *to_parse);
void	init_path(t_cmd *cmd);
void	real_subshell_or_not(t_cmd **cmds);
size_t	skip_redirect(char *to_parse, size_t i);
t_files	*copy_files(t_data *data, char *to_parse, int k, int j);
/*-----------------INITIALIZATION-----------------*/

/*-----------------PARSER-----------------*/
int		valid_quotes(t_data *data, char *to_parse);
int		valid_parentheses(char *to_parse, int *open, size_t i);
int		length_word(char *to_parse, size_t j);
int		check_dollars(char c);
int		char_is_quote(char c);
int		skip_next_stop(char *to_clean);
int		valid_format_token(char *to_parse);
int		unvalid_line(t_data *data, char *line, char **rescue_cmd);
int		valid_double(char *to_parse, size_t i);
void	rescue_command(t_data *data, char **rescue_cmd, int err);
char	*is_shell_variable(t_data *data, char *line);
char	*cleaner(t_data *data, char *to_clean);
char	*clean_(t_data *data, char *to_clean, int skip);
char	*is_valid_expand(t_data *data, char *to_check);
char	*clean_lines(t_data *data, char *line, int expand);
void	clean_cmd(t_cmd *cmd);
void	skip_reverse(char *to_parse, int *i, int quote);
void	clean_files(t_cmd *cmd);
void	back_to_space(char **tab);
size_t	copy_slash(char *to_clean, char *res, size_t *v);
size_t	copy_expands_in_str(char *res, char quote, t_node **node);
size_t	slash_len(char *to_clean, size_t i, size_t *len);
size_t	copy(char *line, char *res, int quoted);
size_t	copy_expands_quote(
			char *to_clean, char *res, size_t *v, t_node **expands);
size_t	copy_single_quote(char *to_clean, char *res, size_t *i);
size_t	handle_expands(
			t_data *data, t_node **expands, char *to_clean, size_t *len);
size_t	handle_quote_expands(
			t_data *data, t_node **expands, char *to_clean, size_t *len);
/*-----------------PARSER-----------------*/

/*-----------------BUILT_IN-----------------*/
char	*get_var_line(char *line);
char	*find_alias_node(t_data *data, char *line);
char	*from_tab_to_line(t_cmd *cmd, char **tab);
int		where_to_write(t_data *data, t_cmd *cmd);
int		check_line(char *line);
int		check_line_alias(char *line);
int		log_files_alias(char *alias, int err_code, int line);
int		built_in(t_data *data, t_cmd *cmd, int fork);
int		exit_process(t_data *data, t_cmd *cmd, int fork);
int		cd(t_data *data, t_cmd *cmd);
int		echo(t_data *data, t_cmd *cmd);
int		populate_alias(char *line);
int		open_check_files_built_in(t_cmd *cmd, t_files **tab);
int		close_fd_built_in(int *fd);
int		print_err_built_in(t_cmd *cmd, char *str, int type);
int		check_alias(t_node *alias, char *line);
int		set_up_alias(t_data *data, t_node *node, t_node *alias);
int		close_redirection(t_cmd *cmd);
int		set_in_redirection_built_in(t_cmd *cmd);
int		pwd(t_data *data, t_cmd *cmd);
int		env(t_data *data, t_cmd *cmd);
int		unset(t_cmd *cmd, t_env *env);
int		alias(t_data *data, t_cmd *cmd);
int		print_alias(t_data *data, t_cmd *cmd);
int		export(t_cmd *cmd, t_env *env);
int		unalias(t_cmd *cmd);
void	is_built_in(t_cmd *cmd);
void	set_node_alias(t_data *data, t_node *node);
void	handle_alias_node(t_data *data, t_cmd *cmd, char *res, char *line);
void	print_alias_node(t_data *data, t_cmd *cmd, char *line);
void	make_export(t_env *env, char *line);
void	alias_(t_data *data, t_cmd *cmd, char *line);
void	populate(t_data *data, char *file);
void	from_alias_to_hero(t_data *data, t_cmd *cmd, char **tab);
void	close_all(t_data *data, t_cmd *cmd);
void	skip_(char *to_parse, size_t *i, int quote);
t_node	*find_(t_data *data, char *line);
/*-----------------BUILT_IN-----------------*/

/*-----------------EXECUTION-----------------*/
int		prepare_next_step(t_data *data, t_cmd **cmd, char *stop, int *i);
void	set_out_redirection(t_cmd *cmd);
void	set_in_redirection(t_cmd *cmd);
int		pipe_par(t_cmd **cmds);
int		is_subshell(t_data *data, t_cmd **cmds, int *i);
void	clean_s_pipes(t_data *data);
void	executing(t_data *data, t_cmd **cmds);
void	run_cmd(t_cmd *cmd);
void	wait_all_child(t_data *data, t_cmd **cmds);
void	open_check_files(t_data *data, t_cmd *cmd, t_files **tab);
void	close_fd(t_data *data, char *str, int *fd);
void	handle_pipes(t_data *data, t_cmd *cmd);
void	close_both_pipes(t_data *data, int pipes[2], int *inited);
void	open_here_doc(t_data *data, t_cmd **cmds);
void	set_redirections_files(t_cmd *cmd);
void	init_pipes(t_data *data, int pipes[2], int *inited);
void	cmd_base_setup(t_cmd *cmd);
/*-----------------EXECUTION-----------------*/

/*-----------------PARENTHESES-----------------*/
int		end_cmd_par(t_cmd **cmds, size_t i);
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
int		fork_docs(t_data *data, t_doc **head);
int		len_files_tab(t_files **tab);
void	ft_lst_add_front_(t_doc **node, t_doc *new);
void	set_node(t_data *data, t_files **tab);
void	close_all_pipes(t_data *data, t_doc **head, int read_, int write_);
void	exit_(int signal);
void	clean_here_doc(t_data *data, t_doc **head);
void	set_up_signals(void);
/*-----------------HERE_DOC_UTILS-----------------*/
#endif
