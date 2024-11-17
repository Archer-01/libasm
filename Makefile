NAME    := libasm.a
SRC     := $(wildcard *.s)
TESTS   := test test_bonus

# ----------------------------------------

AS      := nasm
ASFLAGS := -f elf64
ARFLAGS := rcs
CFLAGS  := -Wall -Wextra -Werror -fpie
LDFLAGS := -pie
LDLIBS  := -L. -lasm

# ----------------------------------------

M_SRC   := $(filter-out %_bonus.s, $(SRC))
M_OBJ   := $(M_SRC:.s=.o)

all: $(NAME)

$(NAME): $(M_OBJ)
	$(AR) $(ARFLAGS) $@ $^

# ----------------------------------------

T_SRC   := test.c
T_OBJ   := $(T_SRC:.c=.o)

test: $(T_OBJ) $(NAME)

# ----------------------------------------

B_SRC   := $(filter %_bonus.s, $(SRC))
B_OBJ   := $(B_SRC:.s=.o)

bonus: $(B_OBJ) $(M_OBJ)
	$(AR) $(ARFLAGS) $(NAME) $^

$(B_OBJ): $(M_OBJ)

# ----------------------------------------

TB_SRC  := test_bonus.c
TB_OBJ  := $(TB_SRC:.c=.o)

test_bonus: $(TB_OBJ) bonus
	$(CC) $(LDFLAGS) $< $(LDLIBS) -o $@

# ----------------------------------------

clean:
	$(RM) *.o

fclean: clean
	$(RM) $(NAME) $(TESTS)

re: fclean all

.PHONY: all clean fclean re bonus
