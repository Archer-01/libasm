#include "libasm.h"
#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_STRLEN(s) assert(strlen(s) == ft_strlen(s))
#define TEST_STRCPY(dst, src) assert(strcmp(strcpy(dst, src), ft_strcpy(dst, src)) == 0)
#define TEST_STRCMP(s1, s2) assert(strcmp(s1, s2) == ft_strcmp(s1, s2))

void	handler(int sig)
{
	if (sig == SIGABRT)
	{
		fputs("Some tests failed!\n", stderr);
		exit(EXIT_FAILURE);
	}
}

int main(void)
{
	signal(SIGABRT, handler);

	// ft_strlen
	{
		TEST_STRLEN("");
		TEST_STRLEN("libasm");
		TEST_STRLEN("Hello, World!\n");
	}

	// ft_strcpy
	{
		char dst[BUFSIZ];
		TEST_STRCPY(dst, "");
		TEST_STRCPY(dst, "libasm");
		TEST_STRCPY(dst, "Hello, World");
	}

	// ft_strcmp
	{
		TEST_STRCMP("", "");
		TEST_STRCMP("libasm", "libasm");
		TEST_STRCMP("", "abc");
		TEST_STRCMP("abc", "");
		TEST_STRCMP("abcde", "abcdf");
		TEST_STRCMP("abcdf", "abcde");
		TEST_STRCMP("abc", "abcdef");
		TEST_STRCMP("abcdef", "abc");
	}

	puts("All tests passed");
	return (0);
}
