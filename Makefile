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

SRCDIR = src/

CONTROLLERDIR = $(SRCDIR)controller/

MODELDIR = $(SRCDIR)model/

VIEWDIR = $(SRCDIR)view/

OBJDIR = obj/

SRC = main.c init.c free.c parsing.c util.c sort.c messages.c all_steps.c\
	colors.c

OBJ = $(SRC:.c=.o)

.PHONY: all clean fclean

%.o: $(CONTROLLERDIR)%.c
	@$(C) $(CFLAG) -c $< $(INC)

%.o: $(MODELDIR)%.c
	@$(C) $(CFLAG) -c $< $(INC)

%.o: $(VIEWDIR)%.c
	@$(C) $(CFLAG) -c $< $(INC)	

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(PRINTFDIR)
	@$(C) $(CFLAG) -o $(NAME) $(OBJ) $(LIBS)
	@echo "\e[38;5;82m$(NAME) compilation is done\033[0m"

clean:
	@make clean -C $(PRINTFDIR)
	@/bin/rm -f $(OBJ) *~
	@echo "\e[93mobject files have been cleaned\033[0m"

fclean: clean
	@make fclean -C $(PRINTFDIR)
	@/bin/rm -f $(NAME)
	@echo "\e[31m$(NAME) has been removed\033[0m"

re: fclean all

#\e[5codem\e[25m blink