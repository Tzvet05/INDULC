# Compilation parameters

NAME :=	indulc

CC :=	clang

LIB_INDULC :=		indulc
LIB_CJSON :=		cjson
LIB_BLUEPRINT :=	blueprint

NAME_LIB_INDULC :=	lib$(LIB_INDULC).a
NAME_LIB_CJSON :=	lib$(LIB_CJSON).so
NAME_LIB_BLUEPRINT :=	lib$(LIB_BLUEPRINT).so

CFLAGS =	-Wall -Wextra -Wconversion -Wpedantic
LDFLAGS =	-L$(DIR_LIB_INDULC) -L$(DIR_LIB_CJSON)$(DIR_BUILD) -L$(DIR_LIB_BLUEPRINT) -Wl,-rpath,$(DIR_LIB_CJSON)$(DIR_BUILD):$(DIR_LIB_BLUEPRINT)
LDLIBS =	-l$(LIB_INDULC) -l$(LIB_CJSON) -l$(LIB_BLUEPRINT)

# Directories

DIR_HDR :=	hdr/
DIR_SRC :=	src/
DIR_OBJ :=	obj/

DIR_BUILD :=	build/
DIR_INCLUDE :=	include/

DIR_LIB_INDULC :=	lib/
DIR_LIB_CJSON :=	submodules/cJSON/
DIR_LIB_BLUEPRINT :=	submodules/Factorio_Json_to_blueprint/

DIR_ARG :=	arguments/
DIR_FIL :=	files/
DIR_ISA :=	isa/
DIR_TOK :=	tokenization/
DIR_PRE :=	preprocessing/
DIR_SYM :=	symbol_table/
DIR_SYN :=	syntax/
DIR_MAC :=	machine_code/
DIR_SIG :=	signals/
DIR_BLU :=	blueprint/
DIR_OUT :=	output_writing/
DIR_UTI :=	utils/

# Colors

COLOR_DEFAULT :=	\033[0m
COLOR_GREEN :=		\033[32;1m
COLOR_BLUE :=		\033[34;1m
COLOR_WHITE :=		\033[97;1m

# Source headers

HDR :=	$(DIR_HDR) \
	$(DIR_LIB_INDULC)$(DIR_HDR) \
	$(DIR_LIB_CJSON) \
	$(DIR_LIB_BLUEPRINT)$(DIR_INCLUDE)

# Source code

SRC :=	main.c \
	$(DIR_ARG)get.c \
	$(DIR_ARG)check.c \
	$(DIR_ARG)exec_options.c \
	$(DIR_ISA)load.c \
	$(DIR_ISA)check.c \
	$(DIR_ISA)get.c \
	$(DIR_ISA)utils.c \
	$(DIR_ISA)free.c \
	$(DIR_FIL)check.c \
	$(DIR_FIL)init.c \
	$(DIR_FIL)free.c \
	$(DIR_TOK)tokenization.c \
	$(DIR_TOK)free.c \
	$(DIR_PRE)preprocessing.c \
	$(DIR_PRE)check.c \
	$(DIR_PRE)free.c \
	$(DIR_SYM)building.c \
	$(DIR_SYM)check.c \
	$(DIR_SYM)free.c \
	$(DIR_SYN)analysis.c \
	$(DIR_SYN)define.c \
	$(DIR_SYN)label.c \
	$(DIR_SYN)instruction.c \
	$(DIR_MAC)generation.c \
	$(DIR_MAC)get_operand.c \
	$(DIR_MAC)utils.c \
	$(DIR_SIG)load.c \
	$(DIR_SIG)check.c \
	$(DIR_SIG)get.c \
	$(DIR_SIG)utils.c \
	$(DIR_SIG)free.c \
	$(DIR_BLU)build_json.c \
	$(DIR_BLU)build_string.c \
	$(DIR_OUT)write.c \
	$(DIR_UTI)parse_json_file.c \
	$(DIR_UTI)free.c \
	$(DIR_UTI)cmp.c \
	$(DIR_UTI)is.c

# Compiled objects

OBJ :=	$(addprefix $(DIR_OBJ), $(SRC:.c=.o))

# Compilation

$(NAME) : $(OBJ) $(NAME_LIB_INDULC) $(NAME_LIB_CJSON) $(NAME_LIB_BLUEPRINT)
	@ $(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) $(LDLIBS) -o $(NAME)
	@ echo "$(COLOR_WHITE)[$(NAME)] - $(COLOR_GREEN)Executable ($(NAME)) compiled.$(COLOR_DEFAULT)"

$(DIR_OBJ)%.o : $(DIR_SRC)%.c
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $(addprefix -I, $(HDR)) -c $^ -o $@

# Libraries

$(NAME_LIB_INDULC) :
	@ make -s -C $(DIR_LIB_INDULC)

$(NAME_LIB_CJSON) :
	@ cmake -DCMAKE_POLICY_VERSION_MINIMUM=4.0 -DENABLE_CJSON_TEST=Off -B$(DIR_LIB_CJSON)$(DIR_BUILD) -S$(DIR_LIB_CJSON) > /dev/null
	@ make -s -C $(DIR_LIB_CJSON)$(DIR_BUILD) > /dev/null
	@ echo "$(COLOR_WHITE)[$(NAME_LIB_CJSON)] - $(COLOR_GREEN)Dynamic library ($(NAME_LIB_CJSON)) compiled.$(COLOR_DEFAULT)"

$(NAME_LIB_BLUEPRINT) :
	@ make lib -s -C $(DIR_LIB_BLUEPRINT)

# Rules

all : $(NAME)

fclean :
	@ make fclean -s -C $(DIR_LIB_INDULC)
	@ rm -rf $(DIR_LIB_CJSON)$(DIR_BUILD)
	@ echo "$(COLOR_WHITE)[$(NAME_LIB_CJSON)] - $(COLOR_BLUE)Objects cleaned.$(COLOR_DEFAULT)"
	@ echo "$(COLOR_WHITE)[$(NAME_LIB_CJSON)] - $(COLOR_BLUE)Dynamic library ($(NAME_LIB_CJSON)) cleaned.$(COLOR_DEFAULT)"
	@ make fclean -s -C $(DIR_LIB_BLUEPRINT)
	@ rm -rf $(DIR_OBJ)
	@ echo "$(COLOR_WHITE)[$(NAME)] - $(COLOR_BLUE)Objects cleaned.$(COLOR_DEFAULT)"
	@ rm -f $(NAME)
	@ echo "$(COLOR_WHITE)[$(NAME)] - $(COLOR_BLUE)Executable ($(NAME)) cleaned.$(COLOR_DEFAULT)"

clean :
	@ make fclean -s -C $(DIR_LIB_INDULC)
	@ find $(DIR_LIB_CJSON)$(DIR_BUILD) -name "*" 2> /dev/null | tail -n +2 | grep -v "\.so" | xargs rm -rf
	@ echo "$(COLOR_WHITE)[$(NAME_LIB_CJSON)] - $(COLOR_BLUE)Objects cleaned.$(COLOR_DEFAULT)"
	@ make clean -s -C $(DIR_LIB_BLUEPRINT)
	@ rm -rf $(DIR_OBJ)
	@ echo "$(COLOR_WHITE)[$(NAME)] - $(COLOR_BLUE)Objects cleaned.$(COLOR_DEFAULT)"

cleanindulc :
	@ rm -rf $(DIR_OBJ)
	@ echo "$(COLOR_WHITE)[$(NAME)] - $(COLOR_BLUE)Objects cleaned.$(COLOR_DEFAULT)"

re : fclean all

reindulc : cleanindulc all

.PHONY : all fclean clean cleanindulc re reindulc
