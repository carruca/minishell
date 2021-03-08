#include "../include/minishell.h"

t_var	*insertardatos(char *str)
{
	t_var	*new_var;
	char	*aux;
	int		index;
	

	new_var = (t_var *)malloc(sizeof(t_var));
	index = 0;
	while (str[index] != '=')
		index++;
	new_var->nombre = ft_strndup(str, index);
	aux = ft_strchr(str, '=');
	aux++;
	new_var->valor = ft_strdup(aux);
	return (new_var);
}