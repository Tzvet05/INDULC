# Make parameters

NAME =		indulc

COMPILER =	clang

CFLAG =		-Wall -Wextra -Werror

LFLAG =		-lm

LIB =		libindulc.a

MOD =		libcjson.so

# Optional compilation macros

ifeq ($(COMP_BIN_CHAR), 1)
	CFLAG += -D COMP_BIN_CHAR
endif

# Directories

HDR_DIR =	hdr/
SRC_DIR =	src/
OBJ_DIR =	obj/
LIB_DIR =	lib/
MOD_DIR =	submodule/cJSON/
MOD_BUILD_DIR =	build/

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
	$(ISA_DIR)check_isa_syntax.c \
	$(ISA_DIR)get_isa.c \
	$(FIL_DIR)file.c \
	$(TOK_DIR)tokenization.c \
	$(PRE_DIR)preprocessing.c \
	$(SYM_DIR)symbol_table_building.c \
	$(SYN_DIR)syntax_analysis.c \
	$(MAC_DIR)machine_code_generation.c \
	$(UTI_DIR)compilation.c \
	$(UTI_DIR)cmp.c \
	$(FRE_DIR)free_data.c \
	$(FRE_DIR)free_struct.c

# Compiled objects

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

# Compilation

$(NAME) : $(OBJ) $(LIB_DIR)$(LIB) $(MOD_DIR)$(MOD_BUILD_DIR)$(MOD)
	@ $(COMPILER) $(CFLAG) $(LFLAG) $(OBJ) $(LIB_DIR)$(LIB) $(MOD_DIR)$(MOD_BUILD_DIR)$(MOD) -Wl,-rpath,$(MOD_DIR)$(MOD_BUILD_DIR) -o $(NAME)
	@ echo "$(COLOR_WHITE)[$(NAME)] - $(COLOR_GREEN)Executable ($(NAME)) compiled.$(COLOR_DEFAULT)"

$(OBJ_DIR)%.o : $(SRC_DIR)%.c | $(OBJ_DIR) $(addprefix $(OBJ_DIR), $(ARG_DIR) $(ISA_DIR) $(FIL_DIR) $(TOK_DIR) $(PRE_DIR) $(SYM_DIR) $(SYN_DIR) $(MAC_DIR) $(UTI_DIR) $(FRE_DIR)) $(MOD_DIR)$(MOD_BUILD_DIR)
	@ $(COMPILER) $(CFLAG) -I$(HDR_DIR) -I$(LIB_DIR)$(HDR_DIR) -I$(MOD_DIR) -c $^ -o $@

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

$(MOD_DIR)$(MOD_BUILD_DIR) :
	@ mkdir -p $(MOD_DIR)$(MOD_BUILD_DIR)

# Library

$(LIB_DIR)$(LIB) :
	@ make -s -C $(LIB_DIR)

# Submodule

$(MOD_DIR)$(MOD_BUILD_DIR)$(MOD) :
	@ cmake -DENABLE_CJSON_TEST=Off -B$(MOD_DIR)$(MOD_BUILD_DIR) -S$(MOD_DIR) > /dev/null
	@ make -s -C $(MOD_DIR)$(MOD_BUILD_DIR) > /dev/null
	@ echo "$(COLOR_WHITE)[$(MOD)] - $(COLOR_GREEN)Dynamic library ($(MOD)) compiled.$(COLOR_DEFAULT)"

# Rules

all : $(NAME)

fclean :
	@ rm -rf $(OBJ_DIR)
	@ echo "$(COLOR_WHITE)[$(NAME)] - $(COLOR_BLUE)Objects cleaned.$(COLOR_DEFAULT)"
	@ rm -f $(NAME)
	@ echo "$(COLOR_WHITE)[$(NAME)] - $(COLOR_BLUE)Executable ($(NAME)) cleaned.$(COLOR_DEFAULT)"
	@ make fclean -s -C $(LIB_DIR)
	@ rm -rf $(MOD_DIR)$(MOD_BUILD_DIR)
	@ echo "$(COLOR_WHITE)[$(MOD)] - $(COLOR_BLUE)Objects cleaned.$(COLOR_DEFAULT)"
	@ echo "$(COLOR_WHITE)[$(MOD)] - $(COLOR_BLUE)Dynamic library ($(MOD)) cleaned.$(COLOR_DEFAULT)"

clean :
	@ rm -rf $(OBJ_DIR)
	@ echo "$(COLOR_WHITE)[$(NAME)] - $(COLOR_BLUE)Objects cleaned.$(COLOR_DEFAULT)"
	@ make fclean -s -C $(LIB_DIR)
	@ find $(MOD_DIR)$(MOD_BUILD_DIR) -name "*" | tail -n +2 | grep -v "\.so" | xargs rm -rf
	@ echo "$(COLOR_WHITE)[$(MOD)] - $(COLOR_BLUE)Objects cleaned.$(COLOR_DEFAULT)"

cleanindulc :
	@ rm -rf $(OBJ_DIR)
	@ echo "$(COLOR_WHITE)[$(NAME)] - $(COLOR_BLUE)Objects cleaned.$(COLOR_DEFAULT)"

re : fclean all

reindulc : cleanindulc all	

.PHONY : all fclean clean cleanindulc re reindulc
