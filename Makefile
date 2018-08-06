# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/13 18:35:56 by akorzhak          #+#    #+#              #
#    Updated: 2018/01/13 18:35:58 by akorzhak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

C = gcc #-fsanitize=address

CFLAG = -Wall -Wextra -Werror

INC = -I ./includes -I ./ft_printf/includes

PRINTFDIR = ft_printf/

PRINTF = $(PRINTFDIR)libftprintf.a

LIBS = -L ./ft_printf -lftprintf

SRCDIR = src

SRC = main.c init.c free.c parsing.c util.c messages.c

OBJ = $(SRC:.c=.o)

.PHONY: all clean fclean

%.o: $(SRCDIR)/%.c
	@$(C) $(CFLAG) -c $< $(INC)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(PRINTFDIR)
	@$(C) $(CFLAG) -o $(NAME) $(OBJ) $(LIBS)
	@echo lem-in compilation is \done
clean:
	@make clean -C $(PRINTFDIR)
	@/bin/rm -f $(OBJ) *~
	@echo object files have been cleaned

fclean: clean
	@make fclean -C $(PRINTFDIR)
	@/bin/rm -f $(NAME)
	@echo lem-in has been removed

re: fclean all
