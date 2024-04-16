## ########################################################################## ##
##                                                                            ##
##                                                        :::      ::::::::   ##
##   Makefile                                           :+:      :+:    :+:   ##
##                                                    +:+ +:+         +:+     ##
##   By: vgoncalv <vgoncalv@student.42sp.org.br>    +#+  +:+       +#+        ##
##                                                +#+#+#+#+#+   +#+           ##
##   Created: 2021/09/13 12:31:20 by vgoncalv          #+#    #+#             ##
##   Updated: 2021/09/13 12:31:20 by vgoncalv         ###   ########.fr       ##
##                                                                            ##
## ########################################################################## ##

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = ./src

CLIENT_SRC = $(SRC_DIR)/client.c
SERVER_SRC = $(SRC_DIR)/server.c

CLIENT_BONUS = $(SRC_DIR)/client_bonus.c
SERVER_BONUS = $(SRC_DIR)/server_bonus.c
BONUS_SRC := $(CLIENT_BONUS) $(SERVER_BONUS)

CLIENT = client
SERVER = server

LIBFT_DIR ?= ./libft
LIBS = -L$(LIBFT_DIR)/lib -lft

INCLUDES = $(LIBFT_DIR)/include
INCLUDES := $(addprefix -I,$(INCLUDES))

RM = rm -f

all: $(CLIENT) $(SERVER)

%: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) $< $(LIBS) -o $@

clean:
	make fclean -C $(LIBFT_DIR)
	$(RM) $(CLIENT) $(SERVER)

fclean: clean

re: fclean all

run: re
	./$(SERVER)

.PHONY: all fclean re
