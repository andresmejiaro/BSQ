# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: momil-vo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/22 13:00:51 by momil-vo          #+#    #+#              #
#    Updated: 2022/11/22 13:38:58 by momil-vo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = a.out

FLAGS = -Wextra -Werror -Wall

SRC = m_main.c



all: $(NAME)

$(NAME): 
	@gcc $(FLAGS) $(SRC) -o $(NAME)

clean:
	@rm -f $(NAME)

fclean: clean

re: fclean all

exec: all
	@./$(NAME) | cat -e

run: exec fclean

.PHONY: all clean fclean re exec run
