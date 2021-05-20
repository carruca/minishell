#include "minishell.h"

/*	recibe un string
	verifica si la cadena contiene el caracter =
	lo separa en funcion a eso en nombre y valor
	devuelve una estructura t_var con las variables name y value */

t_var	*array_to_var(char *str)
{
	t_var	*new_var;
	int		index;

	new_var = (t_var *)malloc(sizeof(t_var));
	if (!new_var)
		error_malloc();
	index = 0;
	while (str[index] != '=')
		index++;
	new_var->name = ft_substr(str, 0, index);
	new_var->value = ft_substr(str, index + 1, ft_strlen(&str[index]));
	return (new_var);
}

// recibe una estructura t_var y una longitud
// len es la suma de la cadena de name + = + value
// devuelve un string

char	*string_union(t_var *var, int len)
{
	char	*string;
	int		i;
	int		j;

	string = (char *)malloc((sizeof(char) * len) + 1);
	if (!string)
		error_malloc();
	i = 0;
	while (i < len)
	{
		while (var->name[i])
		{
			string[i] = var->name[i];
			i++;
		}
		string[i] = '=';
		i++;
		j = 0;
		while (var->value[j])
		{
			string[i] = var->value[j];
			j++;
			i++;
		}
	}
	string[i] = '\0';
	return (string);
}

// recibe una lista
// devuelve una tabla de strings

char	**var_to_array(t_lista *lista)
{
	char	**array;
	t_var	*var;
	int		i;
	int		cont;

	i = 0;
	var = NULL;
	array = NULL;
	cont = ft_lst_size_lst(lista);
	array = (char **)malloc(sizeof(char *) * (cont + 1));
	if (!array)
		error_malloc();
	while (i < cont)
	{
		var = lista->content;
		array[i] = string_union(var, ft_strlen(var->name)
				+ ft_strlen(var->value) + 1);
		lista = lista->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}
