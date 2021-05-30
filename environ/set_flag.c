#include "../minishell.h"

void	set_flag(t_var *var, int flags)
{
	var->flags |= flags;
}
