#include "../minishell.h"

void	set_flags(t_var *var)
{
	if (!ft_strcmp(var->name, "_"))
		set_flag(var, ENV_VAR);
	else if (!var->value)
		var->flags |= EXPORT_VAR;
	else
		var->flags |= (EXPORT_VAR | ENV_VAR);
}
