NAME      := libasm.a
SRC       := $(shell find . -type f -name '*.s' -and -not -name '*_bonus.s')
OBJ       := $(SRC:.s=.o)
BONUS_SRC := $(shell find . -type f -name '*_bonus.s')
BONUS_OBJ := $(BONUS_SRC:.s=.o)

TEST_NAME := test
TEST_SRC  := test.c
TEST_OBJ  := $(TEST_SRC:.c=.o)

BONUS_TEST_NAME := test_bonus
BONUS_TEST_SRC  := test_bonus.c
BONUS_TEST_OBJ  := $(BONUS_TEST_SRC:.c=.o)

ARFLAGS := rcs
AS      := nasm
ASFLAGS := -f elf64
CFLAGS  := -fPIE -static-pie

all: $(NAME)

bonus: $(OBJ) $(BONUS_OBJ)
	$(AR) $(ARFLAGS) $(NAME) $^

$(NAME): $(OBJ)
	$(AR) $(ARFLAGS) $@ $^

$(TEST_NAME): $(NAME) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(TEST_OBJ) $(NAME) -o $@

$(BONUS_TEST_NAME): bonus $(BONUS_TEST_OBJ)
	$(CC) $(CFLAGS) $(BONUS_TEST_OBJ) $(NAME) -o $@

clean:
	$(RM) $(OBJ) $(BONUS_OBJ) $(TEST_OBJ) $(BONUS_TEST_OBJ)

fclean: clean
	$(RM) $(NAME) $(TEST_NAME) $(BONUS_TEST_NAME)

re: fclean all

.PHONY: all clean fclean re bonus
