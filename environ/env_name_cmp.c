#include "../minishell.h"

int	env_name_cmp(void *name, void *var)
{
	char	*name_tmp;
	t_var	*var_tmp;

	name_tmp = name;
	var_tmp = var;
	return (ft_strcmp(name_tmp, var_tmp->name) != 0);
}
