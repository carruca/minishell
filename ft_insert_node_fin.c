#include "minishell.h"

/*	recibe la direccion de memoria de una lista y un nuevo nodo
	agrega un nodo al final de la lista*/

int	ft_insert_nodo_fin(t_lista **lst, t_lista *new)
{
	t_lista	*aux;

	aux = *lst;
	if (!(*lst))
		*lst = new;
	else if (new != NULL)
	{
		while (aux->next != NULL)
			aux = aux->next;
		new->prev = aux;
		aux->next = new;
		return (1);
	}
	return (0);
}
