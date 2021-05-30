#include "../minishell.h"

void	free_var(void *var)
{
	t_var	*tmp;

	tmp = var;
	free(tmp->name);
	if (tmp->value)
		free(tmp->value);
	free(tmp);
	tmp = NULL;
}
