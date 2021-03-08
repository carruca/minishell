#include "libft.h"

t_list	*ft_lstfind(t_list *lst, void *content, int (*cmp)(void *, void *))
{
	if (lst && cmp)
		while (lst)
		{
			if (!cmp(content, lst->content))
				return (lst);
			lst = lst->next;
		}
	return (NULL);
}
