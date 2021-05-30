#include "../minishell.h"

int	modify_value(char *value, t_var *var)
{
	char	*str;

	if (!value)
		return (1);
	str = ft_strdup(value);
	free(var->value);
	var->value = str;
	set_flags(var);
	return (1);
}
