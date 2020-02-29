# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tbruinem <tbruinem@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/02/29 12:38:30 by tbruinem       #+#    #+#                 #
#    Updated: 2020/02/29 22:08:45 by tbruinem      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

#----------------------------------VARIABLES-----------------------------------

NAME = minishell
SRC =	main.c \
		ft_echo.c
OBJ = $(SRC:.c=.o)

#----------------------------------PATHS---------------------------------------

SRC_DIR = src/
OBJ_DIR = obj/
INCL_DIR = include/
LIB_DIR = lib/

#----------------------------------FLAGS---------------------------------------

FLAGS = -I $(INCL_DIR)
ifndef DEV
	FLAGS += -Wall -Wextra -Werror
endif

ifeq ($(DEBUG),1)
	FLAGS += -g
endif
ifeq ($(DEBUG),2)
	FLAGS += -g -fsanitize=address
endif

#----------------------------------TAIL----------------------------------------

TAIL = -I $(LIB_DIR)libext/incl/ -L $(LIB_DIR)libext/ -lext

#----------------------------------DEFINES-------------------------------------

DEFINES = 

#----------------------------------RULES---------------------------------------

all: $(NAME)

lib-all:
	make -C $(LIB_DIR)libext all -j8

lib-re:
	make -C $(LIB_DIR)libext re -j8

%.o: %.c
	@$(CC) -c $(FLAGS) $(TAIL) $< -I $(INCL_DIR) -o $(OBJ_DIR)$(notdir $@)

$(NAME): $(addprefix $(SRC_DIR), $(OBJ))
	$(info Generating object files..)
	@$(CC) $(TAIL) $(addprefix $(OBJ_DIR), $(OBJ)) -o $(NAME)
	$(info Succesfully created $(NAME)!)

clean:
	rm -rf $(addprefix $(OBJ_DIR), $(OBJ))

fclean: clean
	rm -rf $(NAME)

re: fclean all
