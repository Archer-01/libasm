#include "libasm_bonus.h"
#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#define TEST_ATOI_BASE(str, base, n) assert(ft_atoi_base(str, base) == n)

void	handler(int sig)
{
	if (sig == SIGABRT)
	{
		fputs("Some tests failed!\n", stderr);
		exit(EXIT_FAILURE);
	}
}

int	main(void)
{
	signal(SIGABRT, handler);

	/* ft_atoi_base */ {
		const char *binary = "01";
		const char *octal = "01234567";
		const char *decimal = "0123456789";
		const char *hexadecimal = "0123456789abcdef";

		// Invalid base
		TEST_ATOI_BASE("000", "0", 0);
		TEST_ATOI_BASE("100", "+01", 0);
		TEST_ATOI_BASE("101", "-01", 0);
		TEST_ATOI_BASE("110", " 01", 0);
		TEST_ATOI_BASE("111", "011", 0);

		// Invalid/Semi-valid tests
		TEST_ATOI_BASE("42sh", decimal, 42);
		TEST_ATOI_BASE("456", "123", 0);

		// Valid tests
		TEST_ATOI_BASE("0", binary, 0);
		TEST_ATOI_BASE("111", binary, 7);
		TEST_ATOI_BASE("777", octal, 0777);
		TEST_ATOI_BASE("1337", decimal, 1337);
		TEST_ATOI_BASE("2a", hexadecimal, 0x2a);
	}

	puts("All tests passed");
	return (0);
}
