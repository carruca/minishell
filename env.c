#include "minishell.h"

int	capture(t_env *_env, char **env)
{
	int	index;

	index = 0;
	_env->lst = NULL;
	while (*env)
	{
		ft_insert_nodo_fin(&_env->lst, ft_lst_new_lst(array_to_var(*env)));
		env++;
		index++;
	}
	return (0);
}
