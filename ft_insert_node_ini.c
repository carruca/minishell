#include "minishell.h"

int	ft_insert_nodo_ini(t_lista **lst, t_lista *new)
{
	if (!*lst)
		*lst = new;
	else if (new)
	{
		new->next = *lst;
		new->prev = NULL;
		if (*lst)
			(*lst)->prev = new;
		*lst = new;
		return (1);
	}
	return (0);
}
