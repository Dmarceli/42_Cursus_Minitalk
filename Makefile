GREEN		=	\e[38;5;118m
YELLOW		=	\e[38;5;226m
RED			=	\e[0;31m
RESET		=	\e[0m

NAME	=
CLIENT	=	client
SERVER	=	server


LIBFT		=	./libft/libft.a
LIBFT_DIR	=	./libft

SRC_CLIENT	=	client.c
SRC_SERVER	=	server.c

INCS		=	-I. -I$(LIBFT_DIR)
CC			=	gcc
CFLAG		=	-Wall -Wextra -Werror
RM			=	rm -f


all: $(SERVER) $(CLIENT)

$(NAME): all

$(SERVER): $(LIBFT)
	@ $(CC) $(CFLAG) $(SRC_SERVER) $(LIBFT) $(INCS) -o $(SERVER)
	@printf "$(GREEN)server ready to execute.\n$(RESET)"

$(CLIENT): $(LIBFT)
	@ $(CC) $(CFLAG) $(SRC_CLIENT) $(LIBFT) $(INCS) -o $(CLIENT)
	@printf "$(GREEN)client ready to execute.\n$(RESET)"


$(LIBFT):
	@ $(MAKE) -C ./libft --silent

clean:
	@ $(RM) $(CLIENT) $(SERVER)
	@printf "client removed.\n"
	@printf "server removed.\n"

fclean:
	@ $(MAKE) fclean -C $(LIBFT_DIR)
	@ $(RM) $(CLIENT) $(SERVER)
	@printf "$(RED)client removed.\n$(RESET)"
	@printf "$(RED)server removed.\n$(RESET)"

re: fclean all 


.PHONY: all clean fclean re