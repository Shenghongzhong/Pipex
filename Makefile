# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: szhong <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/23 09:36:43 by szhong            #+#    #+#              #
#    Updated: 2024/04/28 21:54:53 by szhong           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

YELLOW = \033[0;93m
GREEN = \033[0;92m
MAGENTA = \033[0;95m
DF = \033[0;39m

NAME		:= pipex
CC		:= cc
CFLAGS		:= -Wall -Wextra -Werror -g
SRCS		:= \
		   src/pipex.c \
		   src/utils.c \
		   src/main.c

OBJ_DIR		:= obj
OBJS		:= $(SRCS:%.c = $(OBJ_DIR)/%.o) 

INCLUDE		:= -I ./inc -I ./libft/inc
LIBFT_PATH	:= ./libft
LIBFT		:= $(LIBFT_PATH)/libft.a
LDFLAGS		:= -L$(LIBFT_PATH)
LDLIBS		:= -lft
MAKEFLAGS	:= --no-print-directory 

all: $(NAME)

$(NAME): $(OBJS) | $(LIBFT) $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(NAME)
	@echo "$(YELLOW)[PIPEX] $(GREEN)Build Completed!$(DF)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRCS)
	@$(CC) $(CLFAGS) $(INCLUDE) -c $< -o $@

$(LIBFT):
	@make $(MAKEFLAGS) -C $(LIBFT_PATH) all

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(MAGENTA)[PIPEX] Objects Removed$(DF)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(MAGENTA)[PIPEX] $(NAME) Removed$(DF)"
	@make $(MAKEFLAGS) -C $(LIBFT_PATH) fclean

re:	fclean all

.PHONY: all clean fclean re
