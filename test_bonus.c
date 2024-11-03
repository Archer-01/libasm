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

int	cmp(void *a, void *b)
{
	int	*pa = a;
	int	*pb= b;

	if (*pa > *pb) {
		return 1;
	}
	else if (*pa < *pb) {
		return -1;
	}
	return 0;
}

int	rev_cmp(void *a, void *b)
{
	int	*pa = a;
	int	*pb = b;

	if (*pa > *pb) {
		return -1;
	}
	else if (*pa < *pb) {
		return 1;
	}
	return 0;
}

void	free_fct(void *ptr)
{
	(void) ptr;
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

	/* ft_list_push_front */ {
		t_list	*head = NULL;
		int		arr[] = {1, 21, 42};

		{
			ft_list_push_front(&head, &arr[0]);
			assert(head != NULL);
			assert(*((int*)head->data) == arr[0]);
			assert(head->next == NULL);
		}

		{
			ft_list_push_front(&head, &arr[1]);
			assert(head != NULL);
			assert(*((int*)head->data) == arr[1]);
			assert(head->next != NULL);
			assert(*((int*)head->next->data) == arr[0]);
			assert(head->next->next == NULL);
		}

		{
			ft_list_push_front(&head, &arr[2]);
			assert(head != NULL);
			assert(*((int*)head->data) == arr[2]);
			assert(head->next != NULL);
			assert(*((int*)head->next->data) == arr[1]);
			assert(head->next->next != NULL);
			assert(*((int*)head->next->next->data) == arr[0]);
			assert(head->next->next->next == NULL);
		}
	}

	/* ft_list_size */ {
		t_list	*head = NULL;
		int		arr[] = {1, 21, 42};

		assert(ft_list_size(head) == 0);

		ft_list_push_front(&head, &arr[0]);
		assert(ft_list_size(head) == 1);

		ft_list_push_front(&head, &arr[1]);
		assert(ft_list_size(head) == 2);

		ft_list_push_front(&head, &arr[2]);
		assert(ft_list_size(head) == 3);
	}

	/* ft_list_sort */ {
		t_list	*head = NULL;

		ft_list_sort(&head, &cmp);
		assert(head == NULL);

		int	arr[] = {2, 3, 4, 1, 5};
		for (int i = 0; i < 5; ++i) {
			ft_list_push_front(&head, &arr[i]);
		}

		ft_list_sort(&head, &cmp);
		assert(*((int*)head->data) == 1);
		assert(*((int*)head->next->data) == 2);
		assert(*((int*)head->next->next->data) == 3);
		assert(*((int*)head->next->next->next->data) == 4);
		assert(*((int*)head->next->next->next->next->data) == 5);

		ft_list_sort(&head, &rev_cmp);
		assert(*((int*)head->data) == 5);
		assert(*((int*)head->next->data) == 4);
		assert(*((int*)head->next->next->data) == 3);
		assert(*((int*)head->next->next->next->data) == 2);
		assert(*((int*)head->next->next->next->next->data) == 1);
	}

	/* ft_list_remove_if */ {
		{
			t_list	*head = NULL;
			int	arr[] = {6, 5, 4, 3, 2, 1};

			// Remove element from empty list
			ft_list_remove_if(&head, &arr[0], &cmp, &free_fct);
			assert(head == NULL);

			for (int i = 1; i <= 5; ++i) {
				ft_list_push_front(&head, &arr[i]);
			}

			// Remove first element
			ft_list_remove_if(&head, &arr[5], &cmp, &free_fct);
			assert(ft_list_size(head) == 4);
			assert(*((int*)head->data) == 2);
			assert(*((int*)head->next->data) == 3);
			assert(*((int*)head->next->next->data) == 4);
			assert(*((int*)head->next->next->next->data) == 5);
			assert(head->next->next->next->next == NULL);

			// Remove last element
			ft_list_remove_if(&head, &arr[1], &cmp, &free_fct);
			assert(ft_list_size(head) == 3);
			assert(*((int*)head->data) == 2);
			assert(*((int*)head->next->data) == 3);
			assert(*((int*)head->next->next->data) == 4);
			assert(head->next->next->next == NULL);

			// Remove middle element
			ft_list_remove_if(&head, &arr[3], &cmp, &free_fct);
			assert(ft_list_size(head) == 2);
			assert(*((int*)head->data) == 2);
			assert(*((int*)head->next->data) == 4);
			assert(head->next->next == NULL);

			ft_list_remove_if(&head, &arr[4], &cmp, &free_fct);
			assert(ft_list_size(head) == 1);
			assert(*((int*)head->data) == 4);
			assert(head->next == NULL);

			// Remove non-existing element
			ft_list_remove_if(&head, &arr[0], &cmp, &free_fct);
			assert(ft_list_size(head) == 1);
			assert(*((int*)head->data) == 4);
			assert(head->next == NULL);

			// Remove sole element
			ft_list_remove_if(&head, &arr[2], &cmp, &free_fct);
			assert(head == NULL);
		}

		{
			t_list	*head = NULL;
			int		arr[] = { 1, 2, 1, 3, 2, 3 };

			for (int i = 0; i < 6; ++i) {
				ft_list_push_front(&head, &arr[i]);
			}


			ft_list_remove_if(&head, &arr[0], &cmp, &free_fct);
			assert(ft_list_size(head) == 4);
			assert(*((int*)head->data) == 3);
			assert(*((int*)head->next->data) == 2);
			assert(*((int*)head->next->next->data) == 3);
			assert(*((int*)head->next->next->next->data) == 2);

			ft_list_remove_if(&head, &arr[1], &cmp, &free_fct);
			assert(ft_list_size(head) == 2);
			assert(*((int*)head->data) == 3);
			assert(*((int*)head->next->data) == 3);

			ft_list_remove_if(&head, &arr[3], &cmp, &free_fct);
			assert(head == NULL);
		}
	}

	puts("All tests passed");
	return (0);
}
