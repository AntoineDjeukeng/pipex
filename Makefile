# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adjeuken <adjeuken@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/04 14:45:59 by adjeuken          #+#    #+#              #
#    Updated: 2025/08/12 11:33:31 by adjeuken         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = pipex
BONUS_NAME  = pipex_bonus

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -I./libft -I./utils

LIBFT_DIR   = ./libft
LIBFT_LIB   = $(LIBFT_DIR)/libft.a

SRC         = main.c ft_execve.c ft_error.c ft_childrens.c cleanup.c pipex_utils.c
SRCS_MAIN   = parse_arguments.c $(SRC)
OBJS_MAIN   = $(SRCS_MAIN:.c=.o)

SRCS_BONUS  = parse_arguments_bonus.c $(SRC)
OBJS_BONUS  = $(SRCS_BONUS:.c=.o)

# Default rule builds both binaries
all: $(LIBFT_LIB) $(NAME) $(BONUS_NAME)

$(NAME): $(OBJS_MAIN)
	$(CC) $(CFLAGS) $(OBJS_MAIN) $(LIBFT_LIB) -o $(NAME)

$(BONUS_NAME): $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT_LIB) -o $(BONUS_NAME)

# Build libft
$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT_DIR)

# Object rule
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Bonus rule
bonus: $(BONUS_NAME)

# Clean rules
clean:
	rm -f $(OBJS_MAIN) $(OBJS_BONUS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all bonus clean fclean re
