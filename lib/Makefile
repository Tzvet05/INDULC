# Make parameters

NAME =		libindulc.a

COMPILER =	clang

CFLAG =		-Wall -Wextra -Werror

# Directories

HDR_DIR =	hdr/
OBJ_DIR =	obj/
SRC_DIR =	src/

LST_DIR = 	lst/

# Colors

COLOR_DEFAULT =	\033[0m
COLOR_GREEN =	\033[1;38;5;2m
COLOR_BLUE =	\033[1;38;5;4m
COLOR_WHITE =	\033[1;38;5m

# Source code

SRC =	$(LST_DIR)lst_size.c \
	$(LST_DIR)lst_new_back.c \
	$(LST_DIR)lst_clear.c \
	$(LST_DIR)lst_last.c \
	$(LST_DIR)lst_find_index.c \
	$(LST_DIR)lst_get_node.c \
	$(LST_DIR)lst_find.c

# Compiled objects

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

# Compilation

$(NAME) : $(OBJ)
	@ echo "$(COLOR_WHITE)[$(NAME)] - $(COLOR_GREEN)Archive ($(NAME)) compiled.$(COLOR_DEFAULT)"
	@ ar rcs $(NAME) $(OBJ)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c | $(OBJ_DIR) $(addprefix $(OBJ_DIR), $(LST_DIR))
	@ $(COMPILER) $(CFLAG) -I $(HDR_DIR) -c $^ -o $@

# Build directories

$(OBJ_DIR) :
	@ mkdir -p $@

$(OBJ_DIR)$(LST_DIR) :
	@ mkdir -p $(OBJ_DIR)$(LST_DIR)

# Rules

all : $(NAME)

fclean : clean
	@ echo "$(COLOR_WHITE)[$(NAME)] - $(COLOR_BLUE)Archive ($(NAME)) cleaned.$(COLOR_DEFAULT)"
	@ rm -f $(NAME)

clean :
	@ echo "$(COLOR_WHITE)[$(NAME)] - $(COLOR_BLUE)Objects cleaned.$(COLOR_DEFAULT)"
	@ rm -rf $(OBJ_DIR)

re : fclean all

.PHONY : all fclean clean re
