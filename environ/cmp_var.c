#include "../minishell.h"

int	cmp_var(t_var *var1, t_var *var2)
{
	return (ft_strcmp(var1->name, var2->name));
}
