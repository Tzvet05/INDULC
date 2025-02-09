# Make parameters

NAME =		indulc

COMPILER =	clang

CFLAG =		-Wall -Wextra -Werror

LFLAG =		-lm

LIB =		libindulc.a

# Directories

LIB_DIR =	lib/
HDR_DIR =	hdr/
SRC_DIR =	src/
OBJ_DIR =	obj/

ARG_DIR =	arguments/
FIL_DIR =	file/
ISA_DIR =	isa/
TOK_DIR =	tokenization/
PRE_DIR =	preprocessing/
SYM_DIR =	symbol_table/
SYN_DIR =	syntax/
MAC_DIR =	machine_code/
UTI_DIR =	utils/
FRE_DIR =	free/

# Colors

COLOR_DEFAULT =		\033[0m
COLOR_GREEN =		\033[1;38;5;2m
COLOR_BLUE =		\033[1;38;5;4m
COLOR_WHITE =		\033[1;38;5;15m

# Source code

SRC =	main.c \
	$(ARG_DIR)argument_checking.c \
	$(ISA_DIR)isa_loading.c \
	$(FIL_DIR)file_opening.c \
	$(TOK_DIR)tokenization.c \
	$(PRE_DIR)preprocessing.c \
	$(SYM_DIR)symbol_table_building.c \
	$(SYN_DIR)syntax_analysis.c \
	$(MAC_DIR)machine_code_generation.c \
	$(UTI_DIR)compilation.c \
	$(UTI_DIR)cmp.c \
	$(UTI_DIR)nbr.c \
	$(FRE_DIR)free_data.c

# Compiled objects

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

# Compilation

$(NAME) : $(LIB_DIR)$(LIB) $(OBJ)
	@ echo "$(COLOR_WHITE)[$(NAME)] - $(COLOR_GREEN)Executable ($(NAME)) compiled.$(COLOR_DEFAULT)"
	@ $(COMPILER) $(CFLAG) $(LFLAG) $(OBJ) $(LIB_DIR)$(LIB) -o $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c | $(OBJ_DIR) $(addprefix $(OBJ_DIR), $(ARG_DIR) $(ISA_DIR) $(FIL_DIR) $(TOK_DIR) $(PRE_DIR) $(SYM_DIR) $(SYN_DIR) $(MAC_DIR) $(UTI_DIR) $(FRE_DIR))
	@ $(COMPILER) $(CFLAG) -I $(HDR_DIR) -I $(LIB_DIR)$(HDR_DIR) -c $^ -o $@

# Build directories

$(OBJ_DIR) :
	@ mkdir -p $@

$(OBJ_DIR)$(ARG_DIR) :
	@ mkdir -p $(OBJ_DIR)$(ARG_DIR)
	
$(OBJ_DIR)$(ISA_DIR) :
	@ mkdir -p $(OBJ_DIR)$(ISA_DIR)

$(OBJ_DIR)$(FIL_DIR) :
	@ mkdir -p $(OBJ_DIR)$(FIL_DIR)

$(OBJ_DIR)$(TOK_DIR) :
	@ mkdir -p $(OBJ_DIR)$(TOK_DIR)

$(OBJ_DIR)$(PRE_DIR) :
	@ mkdir -p $(OBJ_DIR)$(PRE_DIR)

$(OBJ_DIR)$(SYN_DIR) :
	@ mkdir -p $(OBJ_DIR)$(SYN_DIR)

$(OBJ_DIR)$(SYM_DIR) :
	@ mkdir -p $(OBJ_DIR)$(SYM_DIR)

$(OBJ_DIR)$(MAC_DIR) :
	@ mkdir -p $(OBJ_DIR)$(MAC_DIR)

$(OBJ_DIR)$(UTI_DIR) :
	@ mkdir -p $(OBJ_DIR)$(UTI_DIR)

$(OBJ_DIR)$(FRE_DIR) :
	@ mkdir -p $(OBJ_DIR)$(FRE_DIR)

# Library

$(LIB_DIR)$(LIB) :
	@ make -s -C $(LIB_DIR)

# Rules

all : $(NAME)

fclean :
	@ echo "$(COLOR_WHITE)[$(NAME)] - $(COLOR_BLUE)Objects cleaned.$(COLOR_DEFAULT)"
	@ rm -rf $(OBJ_DIR)
	@ echo "$(COLOR_WHITE)[$(NAME)] - $(COLOR_BLUE)Executable ($(NAME)) cleaned.$(COLOR_DEFAULT)"
	@ make fclean -s -C $(LIB_DIR)
	@ rm -f $(NAME)

clean :
	@ echo "$(COLOR_WHITE)[$(NAME)] - $(COLOR_BLUE)Objects cleaned.$(COLOR_DEFAULT)"
	@ make clean -s -C $(LIB_DIR)
	@ rm -rf $(OBJ_DIR)

re : fclean all

.PHONY : all fclean clean re
