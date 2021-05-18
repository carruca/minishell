#include "minishell.h"

// recibe una cadena y busca en cada name de cada nodo hasta encontrarlo
// devuele 0 si lo encuentra y 1 si no
int	search_var_name(void *str, void *var)
{
	t_var	*variable;

	variable = var;
	if (ft_strcmp(str, variable->name))
		return (1);
	return (0);
}

// recibe un nodo(list) y un nuevo value y modifica 
// el contenido de la variable value del nodo por el nuevo
// devuelve la nueva lista

t_list	*modify_value(t_list *list, char *value)
{
	t_var	*var;

	var = list->content;
	free(var->value);
	var->value = ft_strdup(value);
	return (list);
}
