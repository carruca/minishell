#include "../include/minishell.h"

t_var	*variable_create(char *str)
{
	t_var	*new_var;
	int		index;

	new_var = (t_var *)malloc(sizeof(t_var));
	index = 0;
	while (str[index] != '=')
		index++;
	new_var->nombre = ft_substr(str, 0, index);
	new_var->valor = ft_substr(str, index + 1, ft_strlen(&str[index + 1]));
	return (new_var);
}
