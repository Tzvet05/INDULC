# Compilation parameters

NAME :=	libindulc.a

CC :=	clang

CFLAGS =	-Wall -Wextra -Wconversion -Wpedantic

# Directories

DIR_HDR :=	hdr/
DIR_SRC :=	src/
DIR_OBJ :=	obj/

DIR_LST := 	lst/
DIR_PAR :=	parr/
DIR_NBR :=	nbr/
DIR_FIL :=	file/
DIR_BIT :=	bit/

# Colors

COLOR_DEFAULT :=	\033[0m
COLOR_GREEN :=		\033[32;1m
COLOR_BLUE :=		\033[34;1m
COLOR_WHITE :=		\033[97;1m

# Source headers

HDR :=	$(DIR_HDR)

# Source code

SRC :=	$(DIR_LST)new_back.c \
	$(DIR_LST)clear.c \
	$(DIR_LST)last.c \
	$(DIR_LST)find_index.c \
	$(DIR_LST)get_node.c \
	$(DIR_LST)find.c \
	$(DIR_PAR)find.c \
	$(DIR_PAR)clear.c \
	$(DIR_NBR)is_number.c \
	$(DIR_NBR)will_overflow_str.c \
	$(DIR_NBR)will_overflow_int.c \
	$(DIR_NBR)get_number.c \
	$(DIR_NBR)get_charset.c \
	$(DIR_FIL)open.c \
	$(DIR_FIL)get_next_line.c \
	$(DIR_FIL)close.c \
	$(DIR_FIL)free.c \
	$(DIR_BIT)build_mask.c

# Compiled objects

OBJ :=	$(addprefix $(DIR_OBJ), $(SRC:.c=.o))

# Compilation

$(NAME) : $(OBJ)
	@ ar rcs $(NAME) $(OBJ)
	@ echo "$(COLOR_WHITE)[$(NAME)] - $(COLOR_GREEN)Archive ($(NAME)) compiled.$(COLOR_DEFAULT)"

$(DIR_OBJ)%.o : $(DIR_SRC)%.c
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $(addprefix -I,$(HDR)) -c $^ -o $@

# Rules

all : $(NAME)

fclean :
	@ rm -rf $(DIR_OBJ)
	@ echo "$(COLOR_WHITE)[$(NAME)] - $(COLOR_BLUE)Objects cleaned.$(COLOR_DEFAULT)"
	@ rm -f $(NAME)
	@ echo "$(COLOR_WHITE)[$(NAME)] - $(COLOR_BLUE)Archive ($(NAME)) cleaned.$(COLOR_DEFAULT)"

clean :
	@ rm -rf $(DIR_OBJ)
	@ echo "$(COLOR_WHITE)[$(NAME)] - $(COLOR_BLUE)Objects cleaned.$(COLOR_DEFAULT)"

re : fclean all

.PHONY : all fclean clean re
