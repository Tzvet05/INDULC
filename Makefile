# Make parameters

NAME =		indulc

COMPILER =	clang

CFLAG =		-Wall -Wextra -Werror

LIB =		libindulc.a

MOD =		libcjson.so

# Directories

HDR_DIR =	hdr/
SRC_DIR =	src/
OBJ_DIR =	obj/
LIB_DIR =	lib/
MOD_DIR =	submodule/cJSON/
MOD_BUILD_DIR =	build/

STR_DIR =	structures/

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

COLOR_DEFAULT =	\033[0m
COLOR_GREEN =	\033[1;38;5;2m
COLOR_BLUE =	\033[1;38;5;4m
COLOR_WHITE =	\033[1;38;5;15m

# Source headers

HDR =	$(HDR_DIR) \
	$(HDR_DIR)$(STR_DIR) \
	$(LIB_DIR)$(HDR_DIR) \
	$(MOD_DIR)

# Source code

SRC =	main.c \
	$(ARG_DIR)get_arguments.c \
	$(ARG_DIR)exec_options.c \
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
	$(UTI_DIR)cmp.c

# Compiled objects

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

# Compilation

$(NAME) : $(OBJ) $(LIB_DIR)$(LIB) $(MOD_DIR)$(MOD_BUILD_DIR)$(MOD)
	@ $(COMPILER) $(CFLAG) $(OBJ) $(LIB_DIR)$(LIB) $(MOD_DIR)$(MOD_BUILD_DIR)$(MOD) -Wl,-rpath,$(MOD_DIR)$(MOD_BUILD_DIR) -o $(NAME)
	@ echo "$(COLOR_WHITE)[$(NAME)] - $(COLOR_GREEN)Executable ($(NAME)) compiled.$(COLOR_DEFAULT)"

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@ mkdir -p $(dir $@)
	@ $(COMPILER) $(CFLAG) $(addprefix -I,$(HDR)) -c $^ -o $@

# Library

$(LIB_DIR)$(LIB) :
	@ make -s -C $(LIB_DIR)

# Submodule

$(MOD_DIR)$(MOD_BUILD_DIR)$(MOD) :
	@ cmake -DCMAKE_POLICY_VERSION_MINIMUM=4.0 -DENABLE_CJSON_TEST=Off -B$(MOD_DIR)$(MOD_BUILD_DIR) -S$(MOD_DIR) > /dev/null
	@ make -s -C $(MOD_DIR)$(MOD_BUILD_DIR) > /dev/null
	@ echo "$(COLOR_WHITE)[$(MOD)] - $(COLOR_GREEN)Dynamic library ($(MOD)) compiled.$(COLOR_DEFAULT)"

# Rules

all : $(NAME)

fclean :
	@ make fclean -s -C $(LIB_DIR)
	@ rm -rf $(MOD_DIR)$(MOD_BUILD_DIR)
	@ echo "$(COLOR_WHITE)[$(MOD)] - $(COLOR_BLUE)Objects cleaned.$(COLOR_DEFAULT)"
	@ echo "$(COLOR_WHITE)[$(MOD)] - $(COLOR_BLUE)Dynamic library ($(MOD)) cleaned.$(COLOR_DEFAULT)"
	@ rm -rf $(OBJ_DIR)
	@ echo "$(COLOR_WHITE)[$(NAME)] - $(COLOR_BLUE)Objects cleaned.$(COLOR_DEFAULT)"
	@ rm -f $(NAME)
	@ echo "$(COLOR_WHITE)[$(NAME)] - $(COLOR_BLUE)Executable ($(NAME)) cleaned.$(COLOR_DEFAULT)"

clean :
	@ make fclean -s -C $(LIB_DIR)
	@ find $(MOD_DIR)$(MOD_BUILD_DIR) -name "*" | tail -n +2 | grep -v "\.so" | xargs rm -rf
	@ echo "$(COLOR_WHITE)[$(MOD)] - $(COLOR_BLUE)Objects cleaned.$(COLOR_DEFAULT)"
	@ rm -rf $(OBJ_DIR)
	@ echo "$(COLOR_WHITE)[$(NAME)] - $(COLOR_BLUE)Objects cleaned.$(COLOR_DEFAULT)"

cleanindulc :
	@ rm -rf $(OBJ_DIR)
	@ echo "$(COLOR_WHITE)[$(NAME)] - $(COLOR_BLUE)Objects cleaned.$(COLOR_DEFAULT)"

re : fclean all

reindulc : cleanindulc all	

.PHONY : all fclean clean cleanindulc re reindulc
