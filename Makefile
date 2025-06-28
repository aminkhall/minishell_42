NAME 	=	minishell
CC 		=	cc

HEADER 	=	minishell.h

CFLAGS 	= 	-Wall -Wextra -Werror 

SRC 	=	./Execution/Builtins/ft_cd.c \
			./Execution/Builtins/util_cd.c\
			./Execution/Builtins/ft_echo.c \
			./Execution/Builtins/ft_env.c \
			./Execution/Builtins/ft_exit.c \
			./Execution/Builtins/ft_export.c \
			./Execution/Builtins/util_exp.c \
			./Execution/Builtins/util_exp2.c \
			./Execution/Builtins/ft_pwd.c \
			./Execution/Builtins/ft_unset.c \
			./Execution/Builtins/is_builtins.c \
			./Execution/Utils/lst_util.c \
			./Execution/Utils/string_util2.c \
			./Execution/Utils/string_util3.c \
			./Execution/Utils/string_util.c \
			./Execution/Utils/string_util4.c \
			./Execution/Utils/string_util5.c \
			./Execution/Utils/string_util6.c\
			./Execution/ft_exec.c \
			./Execution/ft_execve.c \
			./Execution/ft_redir.c \
			./Execution/ft_pipe.c \
			./Execution/util_redir.c \
			./Parsing/expanding.c \
			./Parsing/expandingtwo.c \
			./Parsing/expand_three.c \
			./Parsing/free.c \
			./Parsing/helpers.c \
			./Parsing/helperstw.c \
			./Parsing/lexer.c \
			./Parsing/lexer_utils.c \
			./Parsing/parser.c \
			./Parsing/parser2.c \
			./Parsing/rename.c \
			./Parsing/token.c \
			./Parsing/utils.c \
			./Parsing/minishell.c \
			./Parsing/herdoc.c \
			./Parsing/heredoctw.c \
			./Parsing/lexertwo.c \
			./Parsing/collect_args.c \
			./Parsing/collect_args2.c \
			./Parsing/init_args.c \
			./Parsing/token_utils.c \
			./Parsing/utils2.c \
			./Parsing/signals.c \
			./Parsing/get_val.c \
			./Parsing/get_val_heredoc.c 


OBJ 	= 	${SRC:.c=.o}

all: ${NAME}


${NAME} : ${OBJ}
	 ${CC} ${OBJ} $(CFLAGS) -lreadline  -lncurses -o ${NAME} 

%.o : %.c $(HEADER)
	 ${CC} $(CFLAGS) -c $< -o $@
	
clean :
	@rm -f ${OBJ}

re: fclean all

fclean : clean
	@rm -f ${NAME}
	
.PHONY: all clean fclean re