#ifndef LIBASM_BONUS
#define LIBASM_BONUS

int	ft_atoi_base(const char *str, const char *base);

typedef struct s_list {
	void			*data;
	struct s_list	*next;
} t_list;

void	ft_list_push_front(t_list **begin_list, void *data);

#endif
