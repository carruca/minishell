#include "minishell.h"

int	capture(t_cap *cap, char **env)
{
	int	index;

	index = 0;
	cap->env_lst = NULL;
	while (*env)
	{
		ft_insert_nodo_fin(&cap->env_lst, ft_lst_new_lst(array_to_var(*env)));
		env++;
		index++;
	}
	return (0);
}
