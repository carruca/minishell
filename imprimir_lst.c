#include "minishell.h"

void	imprimir_content(void *cabeza)
{
	t_var	*content;

	content = cabeza;
	printf("Name: %s\n", content->name);
	printf("Value: %s\n", content->value);
}

void	imprimir_lista(t_lista *lst)
{
	ft_lst_iter_lst(lst, imprimir_content);
}

void	imprimir_tabla(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		printf("%s \n", array[i]);
		i++;
	}
	ft_free_tab(array);
}
