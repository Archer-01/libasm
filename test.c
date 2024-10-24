#include "libasm.h"
#include <stdio.h>
#include <string.h>

#define TEST_STRLEN(s) printf("strlen: %2zu | ft_strlen: %2zu\n", strlen(s), ft_strlen(s))
#define TEST_STRCPY(dst, src) printf("strcpy: \"%15s\" | ft_strcpy: \"%15s\"\n", strcpy(dst, src), ft_strcpy(dst, src))

int main(void)
{
	puts("ft_strlen --------------------------------");
	TEST_STRLEN("");
	TEST_STRLEN("libasm");
	TEST_STRLEN("Hello, World!\n");

	puts("\nft_strcpy --------------------------------");
	char dst[BUFSIZ];
	TEST_STRCPY(dst, "");
	TEST_STRCPY(dst, "libasm");
	TEST_STRCPY(dst, "Hello, World");
	return (0);
}
