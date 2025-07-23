NAME = philosphers

SRCS = src/main.c
OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -g -pthread #-Wall -Wextra -Werror

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