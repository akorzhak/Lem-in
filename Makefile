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

PRINTF_DIR = ft_printf/

PRINTF = $(PRINTF_DIR)libftprintf.a

LIBS = -L ./ft_printf -lftprintf

SRC_DIR = src/

CONTROLLER_DIR = $(SRC_DIR)controller/

MODEL_DIR = $(SRC_DIR)model/

VIEW_DIR = $(SRC_DIR)view/

UTIL_DIR = $(MODEL_DIR)util/

FREE_DIR = $(MODEL_DIR)free/

PARSING_DIR = $(MODEL_DIR)parsing/

OBJ_DIR = obj/

SRC = main.c init.c free.c ants.c math.c sort.c messages.c all_steps.c\
	colors.c formats.c result.c dict.c free_lem.c tmp.c save_input.c\
	args.c rooms.c links.c

OBJ = $(SRC:.c=.o)

.PHONY: all clean fclean

%.o: $(CONTROLLER_DIR)%.c
	@$(C) $(CFLAG) -c $< $(INC)

%.o: $(MODEL_DIR)%.c
	@$(C) $(CFLAG) -c $< $(INC)

%.o: $(VIEW_DIR)%.c
	@$(C) $(CFLAG) -c $< $(INC)

%.o: $(UTIL_DIR)%.c
	@$(C) $(CFLAG) -c $< $(INC)

%.o: $(FREE_DIR)%.c
	@$(C) $(CFLAG) -c $< $(INC)

%.o: $(PARSING_DIR)%.c
	@$(C) $(CFLAG) -c $< $(INC)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(PRINTF_DIR)
	@$(C) $(CFLAG) -o $(NAME) $(OBJ) $(LIBS)
	@echo "\e[38;5;82m$(NAME) compilation is done\e[0m"

clean:
	@make clean -C $(PRINTF_DIR)
	@/bin/rm -f $(OBJ) *~
	@echo "\e[93mobject files have been cleaned\e[0m"

fclean: clean
	@make fclean -C $(PRINTF_DIR)
	@/bin/rm -f $(NAME)
	@echo "\e[31m$(NAME) has been removed\e[0m"

re: fclean all

#\e[5codem\e[25m blink