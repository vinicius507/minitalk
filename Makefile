CC = clang
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = ./src

CLIENT_SRC = $(SRC_DIR)/client.c
SERVER_SRC = $(SRC_DIR)/server.c

CLIENT = client
SERVER = server

LIBFTPRINTF_DIR = ./ft_printf
LIBFTPRINTF = $(LIBFTPRINTF_DIR)/libftprintf.a

LIBS = -L$(LIBFTPRINTF_DIR) -lftprintf

INCLUDES = $(LIBFTPRINTF_DIR)/includes $(LIBFTPRINTF_DIR)/libft/includes
INCLUDES := $(addprefix -I,$(INCLUDES))

RM = rm -f

all: $(LIBFTPRINTF) $(CLIENT) $(SERVER)

%: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) $< $(LIBS) -o $@

clean:
	$(RM) $(CLIENT) $(SERVER)

fclean: clean

re: fclean all

run: all
	./$(SERVER)

$(LIBFTPRINTF):
	make -C $(LIBFTPRINTF_DIR)

.PHONY: all fclean re
