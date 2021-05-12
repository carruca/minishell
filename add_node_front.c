#include "minishell.h"

//recibe una lista y un string
//agrega al inicio de la lista el nuevo nodo

void	add_node_front(t_lista **lst, char *str)
{
	while ((*lst)->prev != NULL)
		*lst = (*lst)->prev;
	ft_insert_nodo_ini(&(*lst), ft_lst_new_lst(array_to_var(str)));
}
