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

PARSING_DIR = $(MODEL_DIR)parsing/

MAIN_DIR = $(MODEL_DIR)main/

UTIL_DIR = $(MODEL_DIR)util/

FREE_DIR = $(MODEL_DIR)free/

ROOMS_DIR = $(PARSING_DIR)rooms/

OBJ_DIR = obj/

SRC = main.c init.c get_rooms.c ants.c\
	form_adj_list.c record_name.c args.c\
	links.c save_input.c move_ants.c\
	prepare_way.c set_capacity.c\
	set_levels.c set_links.c set_ways.c\
	sort.c colors.c dict.c formats.c\
	math.c free.c free_lem.c free_links.c\
	free_rooms.c free_turns.c free_ways.c\
	all_steps.c messages.c result.c	  

OBJ = $(SRC:.c=.o)

#colors constants
RED = \e[31m
YELLOW = \e[93m
GREEN = \e[38;5;82m
BLUE = \033[1;34m
RESET = \e[0m

.PHONY: all clean fclean

%.o: $(CONTROLLER_DIR)%.c
	@$(C) $(CFLAG) -c $< $(INC)

%.o: $(MODEL_DIR)%.c
	@$(C) $(CFLAG) -c $< $(INC)

%.o: $(VIEW_DIR)%.c
	@$(C) $(CFLAG) -c $< $(INC)

%.o: $(PARSING_DIR)%.c
	@$(C) $(CFLAG) -c $< $(INC)

%.o: $(MAIN_DIR)%.c
	@$(C) $(CFLAG) -c $< $(INC)

%.o: $(UTIL_DIR)%.c
	@$(C) $(CFLAG) -c $< $(INC)

%.o: $(FREE_DIR)%.c
	@$(C) $(CFLAG) -c $< $(INC)

%.o: $(ROOMS_DIR)%.c
	@$(C) $(CFLAG) -c $< $(INC)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(PRINTF_DIR)
	@$(C) $(CFLAG) -o $(NAME) $(OBJ) $(LIBS)
	@echo "$(GREEN)$(NAME) compilation is done$(RESET)"
	@echo "$(BLUE)usage:$(RESET) ./lem-in [-e] [-a] < map"
	@echo "flags:"
	@echo "$(BLUE)-e$(RESET) error detection"
	@echo "$(BLUE)-a$(RESET) show all steps"

clean:
	@make clean -C $(PRINTF_DIR)
	@/bin/rm -f $(OBJ) *~
	@echo "$(YELLOW)object files have been cleaned$(RESET)"

fclean: clean
	@make fclean -C $(PRINTF_DIR)
	@/bin/rm -f $(NAME)
	@echo "$(RED)$(NAME) has been removed$(RESET)"

re: fclean all
