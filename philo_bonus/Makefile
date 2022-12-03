NAME = philo_bonus
SRCS = main.c ft_parseint.c init.c process.c routine.c routine_print.c routine_utils.c time.c
OBJS = $(SRCS:.c=.o)
DEPS = $(OBJS:.o=.d)

CC = cc
CFLAGS = -MMD -MP -Wall -Wextra -Werror #-g -fsanitize=thread

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

all: $(NAME)

clean:
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

leaks: CFLAGS += -g -DLEAKS
leaks: all

.PHONY: all clean fclean re leaks

-include $(DEPS)
