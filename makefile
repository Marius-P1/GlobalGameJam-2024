##
## EPITECH PROJECT, 2024
## GameJam
## File description:
## Makefile for GameJam / sfml
##

## config
NAME = 			my_game

_SRC =			app/app.cpp \
				main.cpp

SRCDIR = 		src/

SRC =			$(addprefix $(SRCDIR), $(_SRC))

OBJ = 			$(SRC:.cpp=.o)

INC = 			-I./include

FLAGS 	=		-W -Wall -Wextra -Werror -g

MODULES = -lsfml-graphics -lsfml-window -lsfml-system

all: 			$(NAME) clean

##Colors
color_green = /bin/echo -e "\x1b[32m $1\x1b[0m"
color_yellow = /bin/echo -e "\x1b[33m $1\x1b[0m"

##Rules
$(NAME):
				@g++ -o $(NAME) $(SRC) $(INC) $(LIBS) $(MODULES) $(FLAGS)
				@$(call color_green,"Compilation Done ✅ !")
				@$(MAKE) clean -s

clean:
				@rm -f $(OBJ)
fclean: 		clean
				@rm -f $(NAME)

re: 			fclean all

run: re
	clear
	@$(call color_yellow,"🚀:")
	@./$(NAME) $(ARGS)
