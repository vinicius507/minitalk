CC = clang
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = ./src

CLIENT_SRC = $(SRC_DIR)/client.c
SERVER_SRC = $(SRC_DIR)/server.c

CLIENT = client
SERVER = server

RM = rm -f

all: $(CLIENT) $(SERVER)

%: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

fclean:
	$(RM) $(CLIENT) $(SERVER)

re: fclean all

.PHONY: all fclean re
