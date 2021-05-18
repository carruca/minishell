#include "minishell.h"

// recibe una estructura t_var y crea un nodo de la lista

t_lista	*ft_lst_new_lst(void *content)
{
	t_lista	*new;

	new = NULL;
	new = (t_lista *)malloc(sizeof(t_lista));
	if (!new)
		return (NULL);
	new->content = content;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}
