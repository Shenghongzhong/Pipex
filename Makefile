# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: szhong <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/23 09:36:43 by szhong            #+#    #+#              #
#    Updated: 2024/04/23 10:03:37 by szhong           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

YELLOW = \033[0;93m
GREEN = \033[0;92m
DF = \033[0;39m

NAME		:= pipex
CC		:= cc
CFLAGS		:= -Wall -Wextra -Werror -g
PRINTF_PATH	:= ./ft_printf
MAKEFLAGS	:= --no-print-directory 

all: $(NAME)

$(NAME): ft_printf
	@$(CC) $(CFLAGS) -c main.c -I ./ft_printf/include 
	@$(CC) $(CFLAGS)  main.o -L./ft_printf -lftprintf -o $(NAME)

ft_printf:
	@make $(MAKEFLAGS) -C $(PRINTF_PATH) all
clean:
	@make $(MAKEFLAGS) -C $(PRINTF_PATH) clean
	@rm -rf $(NAME)
	@rm -rf main.o
	@echo "\n$(YELLOW)[pipex] $(GREEN)Objects Removed$(DF)"

fclean: clean
	@make $(MAKEFLAGS) -C $(PRINTF_PATH) fclean
	@rm -rf $(NAME)
	@echo "\n$(YELLOW)[pipex] $(GREEN)$(NAME) Removed $(DF)"

re:	fclean all

.PHONY: all clean fclean re ft_printf
