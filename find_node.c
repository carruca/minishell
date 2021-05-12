#include "minishell.h"

/*	recibe una cadena y una lista
	si encuentra la cadena en el elemento nombre de content
	devuelve un puntero al nodo de lo contrario devuelve null*/

char	*find_node(char *str, t_lista *lst)
{
	t_var	*var;

	while (lst)
	{
		var = lst->content;
		if (search_var_name(str, var) == 0)
			return (var->value);
		lst = lst->next;
	}
	return (NULL);
}
