#ifndef LIBASM_BONUS
#define LIBASM_BONUS

int	ft_atoi_base(const char *str, const char *base);

typedef struct s_list {
	void			*data;
	struct s_list	*next;
} t_list;

void	ft_list_push_front(t_list **begin_list, void *data);
int		ft_list_size(t_list *begin_list);
void	ft_list_sort(t_list **begin_list, int (*cmp)(void*, void*));
void	ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(void*, void*), void (*free_fct)(void *));

#endif
