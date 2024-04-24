# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: szhong <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/23 09:36:43 by szhong            #+#    #+#              #
#    Updated: 2024/04/24 18:16:19 by szhong           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

YELLOW = \033[0;93m
GREEN = \033[0;92m
DF = \033[0;39m

NAME		:= pipex
CC		:= cc
CFLAGS		:= -Wall -Wextra -Werror -g
LIBFT_PATH	:= ./libft
MAKEFLAGS	:= --no-print-directory 

all: $(NAME)

$(NAME): ft_printf
	@$(CC) $(CFLAGS) -c pipex.c -I ./libft/inc
	@$(CC) $(CFLAGS)  pipex.o -L./libft -lft -o $(NAME)

ft_printf:
	@make $(MAKEFLAGS) -C $(LIBFT_PATH) all
clean:
	@make $(MAKEFLAGS) -C $(LIBFT_PATH) clean
	@rm -rf $(NAME)
	@rm -rf pipex.o
	@rm -rf outfile
	@echo "\n$(YELLOW)[pipex] $(GREEN)Objects Removed$(DF)"

fclean: clean
	@make $(MAKEFLAGS) -C $(LIBFT_PATH) fclean
	@rm -rf $(NAME)
	@echo "\n$(YELLOW)[pipex] $(GREEN)$(NAME) Removed $(DF)"

re:	fclean all

.PHONY: all clean fclean re ft_printf
