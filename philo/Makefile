NAME = philo
SRCS = main.c routine.c routine_utils.c thread.c time.c ft_parseint.c 
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
