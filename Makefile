SERVER = server
CLIENT = client
NAME = $(SERVER) $(CLIENT)

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS_SERVER = server.c
SRCS_CLIENT = client.c

OBJS_SERVER = $(SRCS_SERVER:.c=.o)
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)

all: $(NAME)

$(NAME): $(SERVER) $(CLIENT)

$(SERVER): $(OBJS_SERVER)
	$(CC) $(CFLAGS) -o $(SERVER) $(OBJS_SERVER)

$(CLIENT): $(OBJS_CLIENT)
	$(CC) $(CFLAGS) -o $(CLIENT) $(OBJS_CLIENT)

clean:
	rm -f $(OBJS_CLIENT) $(OBJS_SERVER)

fclean: clean
	rm -f $(SERVER) $(CLIENT)

re: fclean all

.PHONY: all clean fclean re