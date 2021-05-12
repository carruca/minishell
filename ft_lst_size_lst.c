#include "minishell.h"

int	ft_lst_size_lst(t_lista *lst)
{
	int		size;
	t_lista	*aux;

	aux = lst;
	if (!aux)
		return (0);
	size = 0;
	while (aux != NULL)
	{
		size++;
		aux = aux->next;
	}
	return (size);
}
