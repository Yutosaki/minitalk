SERVER = server
CLIENT = client
SERVER_BONUS = server_bonus
CLIENT_BONUS = client_bonus
NAME = $(SERVER) $(CLIENT)
NAME_BONUS = $(SERVER_BONUS) $(CLIENT_BONUS)

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./ft_printf -I./libft

SRCS_SERVER = src/server.c
SRCS_CLIENT = src/client.c

SRCS_BONUS_SERVER = src/server.c
SRCS_BONUS_CLIENT = src/client.c

OBJS_SERVER = $(SRCS_SERVER:.c=.o)
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)

OBJS_BONUS_SERVER = $(SRCS_BONUS_SERVER:.c=.o)
OBJS_BONUS_CLIENT = $(SRCS_BONUS_CLIENT:.c=.o)

all: $(NAME)

$(SERVER): $(OBJS_SERVER)
	@make -C "ft_printf"
	$(CC) $(CFLAGS) -o $(SERVER) $(OBJS_SERVER) ft_printf/libftprintf.a 

$(CLIENT): $(OBJS_CLIENT)
	@make -C "ft_printf" >/dev/null
	@make -C "libft" >/dev/null
	$(CC) $(CFLAGS) -o $(CLIENT) $(OBJS_CLIENT) ft_printf/libftprintf.a libft/libft.a

bonus: $(NAME_BONUS)

$(SERVER_BONUS): $(OBJS_BONUS_SERVER)
	@make -C "ft_printf"
	$(CC) $(CFLAGS) -o $(SERVER_BONUS) $(OBJS_BONUS_SERVER) ft_printf/libftprintf.a

$(CLIENT_BONUS): $(OBJS_BONUS_CLIENT)
	@make -C "ft_printf" >/dev/null
	@make -C "libft" >/dev/null
	$(CC) $(CFLAGS) -o $(CLIENT_BONUS) $(OBJS_BONUS_CLIENT) ft_printf/libftprintf.a libft/libft.a

clean:
	rm -f $(OBJS_CLIENT) $(OBJS_SERVER) $(OBJS_BONUS_CLIENT) $(OBJS_BONUS_SERVER)
	@make -C "ft_printf" clean >/dev/null
	@make -C "libft" clean >/dev/null

fclean: clean
	rm -f $(SERVER) $(CLIENT) $(SERVER_BONUS) $(CLIENT_BONUS)
	@make -C "ft_printf" fclean >/dev/null
	@make -C "libft" fclean >/dev/null

re: fclean all

.PHONY: all clean fclean re bonus