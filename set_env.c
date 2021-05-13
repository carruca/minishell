#include "minishell.h"

t_var	*change_value(char *str, t_var *var)
{
	char	*tmp;

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
	devuelve un 1 si lo encuentra sino devuelve un 0*/

int	set_env(t_lista *lst, char *name, char *new_value)
{
	t_var	*var;

	while (lst)
	{
		var = lst->content;
		if (search_env_name(name, var) == 0)
		{
			var = change_value(new_value, var);
			return (1);
		}
		lst = lst->next;
	}
	return (0);
}
