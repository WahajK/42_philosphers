NAME = philo

SRCS = \
	src/main.c \
	src/libft_utils.c \
	src/args.c \
	src/time_utils.c \
	src/init.c \
	src/cleanup.c \
	src/monitor.c \
	src/status.c \
	src/actions.c \
	src/philo.c

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -g -pthread -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all