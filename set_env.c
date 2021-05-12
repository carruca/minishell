#include "minishell.h"

t_var	*change_value(char *str, t_var *var)
{
	char	*tmp;

	while (*str != '=')
		str++;
	str++;
	if (ft_strcmp(var->value, str))
	{
		tmp = var->value;
		var->value = str;
		free(tmp);
	}
	return (var);
}

int	search_env_name(char *str, t_var *var)
{
	t_var	*variable;
	char	*name;
	int		i;

	i = 0;
	variable = var;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	name = (char *)malloc(sizeof(char) * (i + 1));
	ft_strlcpy(name, str, i + 1);
	if (ft_strcmp(name, variable->name))
	{
		free(name);
		return (1);
	}
	free(name);
	return (0);
}

/*	recibe una cadena y una lista
	si encuentra la cadena en el elemento nombre de content
	devuelve un puntero al nodo de lo contrario devuelve null*/

int	set_env(char *str, t_lista *lst)
{
	t_var	*var;

	while (lst)
	{
		var = lst->content;
		if (search_env_name(str, var) == 0)
		{
			var = change_value(str, var);
			return (1);
		}
		lst = lst->next;
	}
	return (0);
}
