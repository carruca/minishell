#include "../minishell.h"

int		is_export(t_var *var)
{
	if (var->flags & EXPORT_VAR)
		return (1);
	return (0);
}
