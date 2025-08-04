# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/04 14:45:59 by adjeuken          #+#    #+#              #
#    Updated: 2025/08/04 14:56:44 by adjeuken         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = pipex
BONUS_NAME  = pipex_bonus

CC          = cc
CFLAGS      = -Wall -Wextra -Werror \
              -I./libft \
              -I./utils
LDFLAGS     = -L./libft -lft

LIBFT_DIR   = ./libft
LIBFT_LIB   = $(LIBFT_DIR)/libft.a

SRC         = utils/fork.c
SRCS_MAIN   = main.c $(SRC)
OBJS_MAIN   = $(SRCS_MAIN:.c=.o)

SRCS_BONUS  = main_bonus.c $(SRC)
OBJS_BONUS  = $(SRCS_BONUS:.c=.o)

# Default rule builds both binaries
all: $(NAME) $(BONUS_NAME)

$(NAME): $(OBJS_MAIN) $(LIBFT_LIB)
	$(CC) $(OBJS_MAIN) $(LDFLAGS) -o $@

$(BONUS_NAME): $(OBJS_BONUS) $(LIBFT_LIB)
	$(CC) $(OBJS_BONUS) $(LDFLAGS) -o $@

# Build libft if needed
$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(BONUS_NAME)

clean:
	rm -f $(OBJS_MAIN) $(OBJS_BONUS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all bonus clean fclean re
