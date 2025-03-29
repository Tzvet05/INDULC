# Make parameters

NAME =		indulc

COMPILER =	clang

CFLAG =		-Wall -Wextra -Werror

LIB =		libindulc.a

MOD =		libcjson.so

# Optional compilation settings

ifeq ($(COMP_BIN_CHAR), 1)
	CFLAG += -DCOMP_BIN_CHAR
endif

ifeq ($(COMP_MUTE_MACRO_WARNINGS), 1)
	CFLAG += -DCOMP_MUTE_MACRO_WARNINGS
endif

# Directories

HDR_DIR =	hdr/
SRC_DIR =	src/
OBJ_DIR =	obj/
LIB_DIR =	lib/
MOD_DIR =	submodule/cJSON/
MOD_BUILD_DIR =	build/

ARG_DIR =	arguments/
FIL_DIR =	files/
ISA_DIR =	isa/
TOK_DIR =	tokenization/
PRE_DIR =	preprocessing/
SYM_DIR =	symbol_table/
SYN_DIR =	syntax/
MAC_DIR =	machine_code/
UTI_DIR =	utils/

# Colors

COLOR_DEFAULT =		\033[0m
COLOR_GREEN =		\033[1;38;5;2m
COLOR_BLUE =		\033[1;38;5;4m
COLOR_WHITE =		\033[1;38;5;15m

# Source code

SRC =	main.c \
	$(ARG_DIR)arguments.c \
	$(ISA_DIR)isa_loading.c \
	$(ISA_DIR)check_isa_syntax.c \
	$(ISA_DIR)get_isa.c \
	$(ISA_DIR)isa_utils.c \
	$(ISA_DIR)free_isa.c \
	$(FIL_DIR)files.c \
	$(TOK_DIR)tokenization.c \
	$(TOK_DIR)free_tokens.c \
	$(PRE_DIR)preprocessing.c \
	$(PRE_DIR)preprocessing_utils.c \
	$(PRE_DIR)free_macro.c \
	$(SYM_DIR)symbol_table_building.c \
	$(SYM_DIR)symbol_table_utils.c \
	$(SYM_DIR)free_label.c \
	$(SYN_DIR)syntax_analysis.c \
	$(SYN_DIR)syntax_define.c \
	$(SYN_DIR)syntax_label.c \
	$(SYN_DIR)syntax_instruction.c \
	$(MAC_DIR)machine_code_generation.c \
	$(MAC_DIR)get_operand.c \
	$(UTI_DIR)assembling.c \
	$(UTI_DIR)cmp.c

# Compiled objects

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

# Compilation

$(NAME) : $(OBJ) $(LIB_DIR)$(LIB) $(MOD_DIR)$(MOD_BUILD_DIR)$(MOD)
	@ $(COMPILER) $(CFLAG) $(OBJ) $(LIB_DIR)$(LIB) $(MOD_DIR)$(MOD_BUILD_DIR)$(MOD) -Wl,-rpath,$(MOD_DIR)$(MOD_BUILD_DIR) -o $(NAME)
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
