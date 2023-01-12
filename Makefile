SRCS		= 	minishell.c \
				print.c

SRCS_SIGNAL =	./signal/signal.c

SRCS_BUILT	=	./built_in/env_utils.c

SRCS_INIT	=	./init/init_cmds.c \
				./init/init_files.c \
				./init/init.c \
				./init/init_utils.c \
				./init/init_redirection.c \
				./init/init_env.c \
				./init/init_env_utils.c \
				./init/init_parentheses.c \
				./init/init_path_cmd.c \
				./init/string_utils.c

SRCS_ERROR	=	./error/error_handling.c \
				./error/bad_input_token.c \
				./error/check_parentheses.c

SRCS_CLEAN	=	./clean/free.c \
				./clean/clean_struct.c

SRCS_EXEC	=	./exec/fd.c \
				./exec/command_redirection.c \
				./exec/execute.c \
				./exec/subshell.c \
				./exec/command_utils.c \
				./exec/child.c \
				./exec/here_doc.c \
				./exec/here_doc_utils.c \
				./exec/pipes.c \
				./exec/parentheses.c

SRCS_PARSER	=	./parser/parser.c \
				./parser/quote_utils.c \
				./parser/quote_utils_2.c \
				./parser/parse_double_quote.c \
				./parser/pre_cleaner.c \
				./parser/dollars_utils.c

INCLUDES	= 	-I ./includes

OBJS		= 	$(SRCS:.c=.o) \
				$(SRCS_INIT:.c=.o) \
				$(SRCS_ERROR:.c=.o) \
				$(SRCS_CLEAN:.c=.o) \
				$(SRCS_SIGNAL:.c=.o) \
				$(SRCS_BUILT:.c=.o) \
				$(SRCS_EXEC:.c=.o) \
				$(SRCS_PARSER:.c=.o)

DEPS		= 	$(SRCS:.c=.d) \
				$(SRCS_INIT:.c=.d) \
				$(SRCS_ERROR:.c=.d) \
				$(SRCS_CLEAN:.c=.d) \
				$(SRCS_SIGNAL:.c=.d) \
				$(SRCS_BUILT:.c=.d) \
				$(SRCS_EXEC:.c=.d) \
				$(SRCS_PARSER:.c=.d)

CC			=	cc

CFLAGS		=   -Wall -Wextra -Werror -MMD

MINISHELL	=	minishell

all:			$(MINISHELL)

.c.o :	
				$(CC) -g3 $(CFLAGS) -c $< -o $@

$(MINISHELL):	${OBJS}
				make -C ./libft/ft_printf
				cp ./libft/ft_printf/libprintf.a ./lib
				make -C ./libft
				cp ./libft/libft.a ./lib
				$(CC) $(CFLAGS) ${OBJS} $(INCLUDES) -g3 -L./lib -lft -lprintf -lreadline -o $(MINISHELL)


clean:
				rm -rf $(OBJS)
				rm -rf $(DEPS)
			
fclean:			clean
				make -C ./libft/ft_printf fclean
				make -C ./libft/ fclean
				rm -rf $(MINISHELL) ./lib/libprintf.a ./lib/libft.a 
				

re:				fclean all

-include : 		$(DEPS)

.PHONY:			all clean fclean re