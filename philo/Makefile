NAME			=	philo

DIR_SRCS		=	srcs/
DIR_OBJS		=	objs

SRCS_NAMES		=	main.c parse.c threads.c utils.c eat_sleep_think.c

OBJS_NAMES		=	${SRCS_NAMES:.c=.o}

SRCS			=	$(addprefix $(DIR_SRCS)/,$(SRCS_NAMES))
OBJS			=	$(addprefix $(DIR_OBJS)/,$(OBJS_NAMES))

HEAD			=	-Iincludes/
CC				=	cc
CFLAGS			=	-g3 -Wall -Werror -Wextra -pthread #-fsanitize=thread

all				:	${NAME}

$(NAME):	$(OBJS)
		@echo "\033[33m----Compiling----" .
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
		@echo "\033[32mPhilo Compiled!\n"


$(DIR_OBJS)/%.o: $(DIR_SRCS)/%.c | $(DIR_OBJS)
	$(CC) $(CFLAGS) -c $< -o $@ $(HEAD)

$(DIR_OBJS):
	mkdir -p $(DIR_OBJS)

clean:
	rm -rf ${DIR_OBJS}
	rm -rf ${OBJS}

fclean:	clean
	rm -rf ${NAME}

re:	fclean all

stop:
	rm ${NAME}

.PHONY:	all clean fclean re bonus
