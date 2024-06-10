# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/04 17:00:51 by ibouram           #+#    #+#              #
#    Updated: 2024/06/10 11:50:59 by zderfouf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PARSINGSRC =	parsing/parsing.c parsing/quotes.c parsing/utils.c \
				parsing/add_space.c parsing/syntax_error.c parsing/Tokenizer.c parsing/lin_list.c  main.c parsing/signals.c\
				parsing/utils2.c parsing/expanding.c parsing/ft_split2.c parsing/remove_quotes.c parsing/struct.c \

EXECUTIONSRC = 	execution/builtins/cd.c execution/builtins/echo.c execution/builtins/exit.c execution/builtins/caller.c \
				execution/builtins/export.c execution/builtins/pwd.c execution/builtins/unset.c \
				execution/tools/equals_spliter.c execution/tools/helper_utils.c execution/pipe_execute/executer.c \
				execution/tools/lst_utils.c execution/tools/mini_utils.c execution/tools/split.c execution/tools/string_utils.c \
				execution/pipe_execute/exec_tools.c execution/pipe_execute/file_opener.c \

RM = rm -rf
NAME = minishell
CC = cc
FLAGS = -fsanitize=address -g #-Wall -Wextra -Werror
READLINE = $(shell brew --prefix readline)

PARSINGOBJS = $(PARSINGSRC:.c=.o)
EXECUTIONOBJS = $(EXECUTIONSRC:.c=.o)
MAINOBJS = $(MAINSRC:.c=.o)

all: $(NAME)
	@printf "\033[32m[ ✔ ] %s\n\033[0m" "DONE"
$(NAME): $(PARSINGOBJS) $(EXECUTIONOBJS)
	@$(CC) $(FLAGS) -L$(READLINE)/lib -lreadline $^ -o $@


%.o: %.c minishell.h
	@$(CC) $(FLAGS) -I$(READLINE)/include -c $< -o $@

clean:
	@$(RM) $(PARSINGOBJS) $(EXECUTIONOBJS)

fclean: clean
	@$(RM) $(NAME)
	@printf "\033[32m[ ✔ ] %s\n\033[0m" "Clean"

re: fclean all