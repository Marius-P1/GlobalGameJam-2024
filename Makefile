##
## EPITECH PROJECT, 2024
## GameJam
## File description:
## Makefile for GameJam / sfml
##

## config
NAME = 			SuckerFight

_SRC =			app/App.cpp \
				player/Player.cpp \
				player/Attack.cpp\
				player/Init.cpp\
				map/Map.cpp \
				game/Game.cpp \
				utils/SpriteSheetSimplifier.cpp\
				player/Life.cpp\
				menu/Menu.cpp\
				Main.cpp

SRCDIR = 		src/

SRC =			$(addprefix $(SRCDIR), $(_SRC))

OBJ = 			$(SRC:.cpp=.o)

INC = 			-I./include

FLAGS 	=		-W -Wall -Wextra -Werror -g

MODULES = -l sfml-graphics -l sfml-window -l sfml-system -l sfml-audio

WIN_INCLUDE = 	-I./SFML-2.6.1/include -I./include

WIN_LIBS =		-L./SFML-2.6.1/lib

all: 			$(NAME) clean

##Colors
color_green = @/bin/echo -e "\x1b[32m $1\x1b[0m"
color_yellow = @/bin/echo -e "\x1b[33m $1\x1b[0m"

##Rules

### Take Care !!!! static buil require that the lib is corretly linked in the good order if not you got teribly undefined...
## good linking = no problem 
# here we include static lib in the good order so we dont need .dll anymore / first we take the .rc (contain a icon) and we compile it to .res (resource) then we link it to the .exe
# then compile all source file and link the .exe with the static lib in the good order
win_build:
				$(call color_green,"Compiling Windows files...")
				@x86_64-w64-mingw32-windres win-build.rc -O coff -o win-build.res
				@x86_64-w64-mingw32-g++ $(SRC) -o ./build/win32/$(NAME) -static-libgcc -static-libstdc++ win-build.res $(WIN_INCLUDE) $(WIN_LIBS) -lsfml-graphics-s -lsfml-window-s -lsfml-audio-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32 -lsfml-window -lopenal32 -lFLAC -lvorbisenc -lvorbisfile -lvorbis -logg -DSFML_STATIC
				@cd ./build/win32 && zip -r $(NAME)Win.zip . && mv $(NAME)Win.zip ../
				@$(call color_green,"Windows build Done ✅ !  folder: ./build/$(NAME)Win.zip")
				@$(MAKE) clean -s
$(NAME):
				@g++ -o ./build/linux/$(NAME) $(SRC) $(INC) $(LIBS) $(MODULES) $(FLAGS) 
				@cd ./build/linux && zip -r $(NAME)Linux.zip . && mv $(NAME)Linux.zip ../
				@$(call color_green,"Linux build Done ✅ !  folder: ./build/$(NAME)Linux.zip")
				@$(MAKE) clean -s
clean:
				@rm -f $(OBJ)
fclean: 		clean
				@rm -f $(NAME)

re: 			fclean all

run: re
	clear
	@$(call color_yellow,"🚀:")
	@cd ./build/linux && ./$(NAME) $(ARGS)
