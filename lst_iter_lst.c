#include "minishell.h"

void	ft_lst_iter_lst(t_lista *lst, void (*f)(void *))
{
	while (lst != NULL)
	{
		f(lst->content);
		lst = lst->next;
	}
}
