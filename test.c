#include "libasm.h"
#include <stdio.h>
#include <string.h>

#define TEST_STRLEN(s) printf("strlen: %2zu | ft_strlen: %2zu\n", strlen(s), ft_strlen(s))

int main(void)
{
	puts("ft_strlen --------------------------------");
	TEST_STRLEN("");
	TEST_STRLEN("libasm");
	TEST_STRLEN("Hello, World!\n");
	return (0);
}
