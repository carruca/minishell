#include "minishell.h"

/*
void	ordenar_tabla(char **tabla)
{
	char	*aux;
	char	**ptr;

	while (*tabla)
	{
		ptr = tabla;
		tabla++;
		while (*ptr)
		{
			if (**tabla > **ptr)
			{
				aux = *tabla;
				*tabla = *ptr;
				*ptr = aux;
			}
			else
				ptr++;
		}
		tabla++;
	}
}

void	print_tabla(char **tabla, char *heap)
{
	char	*str;

	while (*tabla)
	{
		ft_putstr_fd(heap, 1);
		if (*tabla)
		{
			str = *tabla;
			while ((*str) != '=')
			{
				ft_putchar(*(str++));
			}
			ft_putchar(*(str++));
			ft_putchar('"');
			while (*str != '\0')
			{
				ft_putchar(*(str++));
			}
			ft_putchar('"');
		}
		ft_putchar('\n');
		tabla++;
	}
}

void	print_export(t_lista *env)
{
	char	**tabla;
	char	*heap;

	tabla = NULL;
	heap = "declare -x ";
	tabla = var_to_array(env);
	ordenar_tabla(tabla);
	print_tabla(tabla, heap);
	ft_free_tab(tabla);
}

int	set_export(int argc, char **cmdline, t_env *_env)
{
	if (argc > 1)
		add_node_before_last(_env->env_lst, &*(++cmdline));
	else
		print_export(_env->env_lst);
	return (1);
}*/
