SERVER = server
CLIENT = client
NAME = $(SERVER) $(CLIENT)

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./ft_printf -I./libft

SRCS_SERVER = server.c
SRCS_CLIENT = client.c

OBJS_SERVER = $(SRCS_SERVER:.c=.o)
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)

all: $(NAME)

$(SERVER): $(OBJS_SERVER)
	@make -C "ft_printf"
	$(CC) $(CFLAGS) -o $(SERVER) $(OBJS_SERVER) ft_printf/libftprintf.a

$(CLIENT): $(OBJS_CLIENT)
	@make -C "ft_printf" >/dev/null
	@make -C "libft" >/dev/null
	$(CC) $(CFLAGS) -o $(CLIENT) $(OBJS_CLIENT) ft_printf/libftprintf.a libft/libft.a

clean:
	rm -f $(OBJS_CLIENT) $(OBJS_SERVER) 
	@make -C "ft_printf" clean >/dev/null
	@make -C "libft" clean >/dev/null

fclean: clean
	rm -f $(SERVER) $(CLIENT)
	@make -C "ft_printf" fclean >/dev/null
	@make -C "libft" fclean >/dev/null

re: fclean all

.PHONY: all clean fclean re