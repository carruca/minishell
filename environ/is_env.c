#include "../minishell.h"

int		is_env(t_var *var)
{
	if (var->flags & ENV_VAR)
		return (1);
	return (0);
}
