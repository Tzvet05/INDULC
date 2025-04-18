# Make parameters

NAME =		libindulc.a

COMPILER =	clang

CFLAG =		-Wall -Wextra -Werror

# Directories

HDR_DIR =	hdr/
OBJ_DIR =	obj/
SRC_DIR =	src/

LST_DIR = 	lst/
PAR_DIR =	parr/
NBR_DIR =	nbr/
FIL_DIR =	file/
BIT_DIR =	bit/

# Colors

COLOR_DEFAULT =	\033[0m
COLOR_GREEN =	\033[1;38;5;2m
COLOR_BLUE =	\033[1;38;5;4m
COLOR_WHITE =	\033[1;38;5m

# Source code

SRC =	$(LST_DIR)lst_new_back.c \
	$(LST_DIR)lst_clear.c \
	$(LST_DIR)lst_last.c \
	$(LST_DIR)lst_find_index.c \
	$(LST_DIR)lst_get_node.c \
	$(LST_DIR)lst_find.c \
	$(PAR_DIR)parr_find.c \
	$(NBR_DIR)is_number.c \
	$(NBR_DIR)will_overflow_str.c \
	$(NBR_DIR)will_overflow_int.c \
	$(NBR_DIR)get_number.c \
	$(NBR_DIR)get_charset.c \
	$(FIL_DIR)open_file.c \
	$(FIL_DIR)close_file.c \
	$(FIL_DIR)get_next_line.c \
	$(BIT_DIR)build_mask.c

# Compiled objects

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

# Compilation

$(NAME) : $(OBJ)
	@ ar rcs $(NAME) $(OBJ)
	@ echo "$(COLOR_WHITE)[$(NAME)] - $(COLOR_GREEN)Archive ($(NAME)) compiled.$(COLOR_DEFAULT)"

$(OBJ_DIR)%.o : $(SRC_DIR)%.c | $(OBJ_DIR) $(addprefix $(OBJ_DIR), $(LST_DIR) $(PAR_DIR) $(NBR_DIR) $(FIL_DIR) $(BIT_DIR))
	@ $(COMPILER) $(CFLAG) -I$(HDR_DIR) -c $^ -o $@

# Build directories

$(OBJ_DIR) :
	@ mkdir -p $@

$(OBJ_DIR)$(LST_DIR) :
	@ mkdir -p $(OBJ_DIR)$(LST_DIR)

$(OBJ_DIR)$(PAR_DIR) :
	@ mkdir -p $(OBJ_DIR)$(PAR_DIR)

$(OBJ_DIR)$(NBR_DIR) :
	@ mkdir -p $(OBJ_DIR)$(NBR_DIR)

$(OBJ_DIR)$(FIL_DIR) :
	@ mkdir -p $(OBJ_DIR)$(FIL_DIR)

$(OBJ_DIR)$(BIT_DIR) :
	@ mkdir -p $(OBJ_DIR)$(BIT_DIR)

# Rules

all : $(NAME)

fclean : clean
	@ rm -f $(NAME)
	@ echo "$(COLOR_WHITE)[$(NAME)] - $(COLOR_BLUE)Archive ($(NAME)) cleaned.$(COLOR_DEFAULT)"

clean :
	@ rm -rf $(OBJ_DIR)
	@ echo "$(COLOR_WHITE)[$(NAME)] - $(COLOR_BLUE)Objects cleaned.$(COLOR_DEFAULT)"

re : fclean all

.PHONY : all fclean clean re
