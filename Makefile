# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlachheb <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/10 13:38:37 by mlachheb          #+#    #+#              #
#    Updated: 2021/06/10 19:26:11 by mlachheb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PIPEX_NAME = pipex

SRC = libft_functions.c functions_args.c ft_split.c file_open_close.c\
	  commands.c

MAIN = pipex.c

BONUS_MAIN = pipex_bonus.c

all: $(PIPEX_NAME)

$(PIPEX_NAME):
	gcc -Wall -Wextra -Werror $(SRC) $(MAIN) -o $(PIPEX_NAME)

bonus:
	gcc -Wall -Wextra -Werror $(SRC) $(BONUS_MAIN) -o $(PIPEX_NAME)

clean:
	echo "No object File to remove"

fclean:
	echo "No Library to remove"

re:
	rm -rf $(PIPEX_NAME)
	gcc -Wall -Wextra -Werror $(SRC) $(MAIN) -o $(PIPEX_NAME)

debug:
	gcc -Wall -Wextra -Werror -g $(SRC) $(MAIN) -o $(PIPEX_NAME)
