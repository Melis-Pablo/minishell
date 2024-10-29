################################################################################
#                                     CONFIG                                   #
################################################################################
NAME		:= minishell
INCLUDES	:= includes
CC			:= gcc
FLAGS		:= -Wall -Wextra -Werror -g -I $(INCLUDES)
################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################
SRCS		:=	main.c \
				srcs/4_env_expand/get_env.c \
				srcs/4_env_expand/envexpand.c \
				srcs/4_env_expand/special_envexpand.c \
				srcs/1_split_tokens/split_tokens_tools.c \
				srcs/1_split_tokens/split_tokens.c \
				srcs/builder.c \
				srcs/5_parser/parser_utils.c \
				srcs/5_parser/parser.c \
				srcs/0_builtins/builtin_utils4.c \
				srcs/0_builtins/m_export.c \
				srcs/0_builtins/builtin_caller.c \
				srcs/0_builtins/m_cd.c \
				srcs/0_builtins/builtin_utils3.c \
				srcs/0_builtins/m_exit.c \
				srcs/0_builtins/builtin_utils.c \
				srcs/0_builtins/builtin_utils2.c \
				srcs/0_builtins/m_unset.c \
				srcs/0_builtins/m_env.c \
				srcs/0_builtins/m_pwd.c \
				srcs/0_builtins/builtin_utils5.c \
				srcs/0_builtins/get_envp.c \
				srcs/0_builtins/m_echo.c \
				srcs/3_syntax_error/syntax_error.c \
				srcs/3_syntax_error/unclosed_quotes.c \
				srcs/6_execute/find_exec.c \
				srcs/6_execute/pipe_case.c \
				srcs/6_execute/execution.c \
				srcs/6_execute/exec_utils.c \
				srcs/2_lexer/lexer.c \
				srcs/2_lexer/lexer_utils.c \
				srcs/utils/str_utils.c \
				srcs/utils/utils2.c \
				srcs/utils/print.c \
				srcs/utils/print2.c \
				srcs/utils/ft_split.c \
				srcs/utils/utils.c \
				srcs/utils/str_utils2.c \
				srcs/cleaner.c \
				srcs/5.1_redirections/redirections.c \
				srcs/5.1_redirections/heredoc.c \
				srcs/5.1_redirections/heredoc_utils.c \
				srcs/5.1_redirections/heredoc_utils2.c \
				srcs/signals.c \

OBJS		:= $(SRCS:.c=.o)

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}
################################################################################
#                                  Makefile  objs                              #
################################################################################
CLR_RMV		:= \033[0m
RED			:= \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN		:= \033[1;36m
RM			:= rm -f

${NAME}:	${OBJS}
			@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
			${CC} ${FLAGS} -o ${NAME} ${OBJS} -lreadline
			@echo "$(GREEN)$(NAME) created[0m ✔️"

all:		${NAME}

bonus:		all

clean:
			@ ${RM} *.o */*.o */*/*.o */*/*/*.o
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"

fclean:		clean
			@ ${RM} ${NAME}
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"

re:			fclean all

cleanly:	all clean

.PHONY:		all clean fclean re cleanly bonus
