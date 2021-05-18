#include "minishell.h"

int	set_env_delete(t_lista *lst, char *str)
{
	t_var	*var;
	t_lista	*aux;

	while (lst)
	{
		var = lst->content;
		if (strcmp(str, var->name) == 0)
		{
			if (lst->next)
			{
				aux = lst;
				lst->prev->next = lst->next;
				lst->next->prev = lst->prev;
				free_node(aux);
				free(aux);
			}
			return (1);
		}
		lst = lst->next;
	}
	return (0);
}

int	ft_delete_node(t_lista *lst, char **str)
{
	while (*str)
	{
		set_env_delete(lst, *str);
		str++;
	}
	return (1);
}
