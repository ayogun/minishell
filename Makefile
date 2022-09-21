# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yogun <yogun@student.42heilbronn.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/18 18:47:42 by yogun             #+#    #+#              #
#    Updated: 2022/09/21 10:18:26 by yogun            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFTDIR = ./lib

CC = gcc

RM = rm -f

FLAGS = -Wall -Wextra -Werror

SRC =	./src/minishell.c \

OBJ = ${SRC:.c=.o}

INCLIBFT = -L./lib -lft
INCREADL = -lreadline -L /opt/homebrew/opt/readline/lib
INCREADH = -I /opt/homebrew/opt/readline/include

.c.o:
	${CC} ${FLAGS} ${INCREADH} -MMD -MP -c $< -o ${<:.c=.o}

${NAME}: ${OBJ}
	@make -C $(LIBFTDIR)
	@echo "Libft has been compiled\n" 
	${CC} ${OBJ} ${INCLIBFT} ${INCREADL} -o ${NAME}
	
all: ${NAME}

bonus: all

clean:
	${RM} ${OBJ}
	@cd $(LIBFTDIR) && $(MAKE) clean

fclean: clean
	${RM} ${NAME}
	@cd $(LIBFTDIR) && $(MAKE) fclean

re: fclean all

.PHONY: all clean fclean re bonus
