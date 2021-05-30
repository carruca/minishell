#include "../minishell.h"

int	increase_shlvl(char *str, t_var *var)
{
	int	tmp;

	(void)str;
	tmp = ft_atoi(var->value);
	free(var->value);
	var->value = ft_itoa(++tmp);
	return (1);
}
