NAME := libasm.a
SRC := $(shell find . -type f -name *.s)
OBJ := $(SRC:.s=.o)

TEST_NAME := test
TEST_SRC := test.c
TEST_OBJ := $(TEST_SRC:.c=.o)

ARFLAGS := rcs
AS := nasm
ASFLAGS := -f elf64
CFLAGS := -fPIE -static-pie

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(ARFLAGS) $@ $^

$(TEST_NAME): $(NAME) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(TEST_OBJ) $(NAME) -o $@

clean:
	$(RM) $(OBJ) $(TEST_OBJ)

fclean: clean
	$(RM) $(NAME) $(TEST_NAME)

re: fclean all
