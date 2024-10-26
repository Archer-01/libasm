#include "libasm.h"
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

	// ft_write
	{
		/* Successful call */ {
			const char *message = "libasm";
			const int fd = open("/dev/null", O_WRONLY, 0);
			const ssize_t ret = ft_write(fd, message, strlen(message));
			assert(ret == strlen(message));
			close(fd);
		}

		/* Bad file descriptor */ {
			const char *message = "libasm";
			const ssize_t ret = ft_write(3, message, strlen(message));
			assert(ret == -1);
			assert(errno == EBADF);
		}

		/* Bad buffer */ {
			const ssize_t ret = ft_write(STDOUT_FILENO, NULL, 42);
			assert(ret == -1);
			assert(errno == EFAULT);
		}
	}

	// ft_read
	{
		/* Pre-tests setup */ {
			const int fd = open("testfile", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
			write(fd, "libasm", 6);
			close(fd);
		}

		/* Successful call */ {
			char buf[BUFSIZ] = {'\0'};
			const int fd = open("testfile", O_RDONLY, 0);
			const ssize_t ret = ft_read(fd, buf, 6);
			assert(ret == 6);
			close(fd);
		}

		/* Bad file descriptor */ {
			char buf[BUFSIZ] = {'\0'};
			const ssize_t ret = ft_read(42, buf, 42);
			assert(ret == -1);
			assert(errno == EBADF);
		}

		/* Bad buffer */ {
			const int fd = open("testfile", O_RDONLY, 0);
			const ssize_t ret = ft_read(fd, NULL, 1);
			assert(ret == -1);
			assert(errno == EFAULT);
			close(fd);
		}

		/* Post-test teardown */ {
			unlink("testfile");
		}
	}

	// ft_strdup
	{
		/* Successful test */ {
			const char *message = "libasm";
			char *dup = ft_strdup(message);
			assert(strcmp(message, dup) == 0);
			free(dup);
		}

		/* Empty string */ {
			char *dup = ft_strdup("");
			assert(strcmp(dup, "") == 0);
			free(dup);
		}

		/* NULL string */ {
			assert(ft_strdup(NULL) == NULL);
		}
	}

	puts("All tests passed");
	return (0);
}
