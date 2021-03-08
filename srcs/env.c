#include "../include/minishell.h"


void imprimirlista(void *cabeza)
{
	t_var *var;
	var = (void *)cabeza;
	
	printf("Nombre = %s \n", var->nombre);
	printf("Valor = %s \n", var->valor);

}

void	capture_env(t_all *mini ,char **env)
{
	mini->lista = NULL;
	while (*env)
	{
		ft_lstadd_back(&mini->lista, ft_lstnew(variable_create(*env)));
		env++;
	}
	ft_lstiter(mini->lista, &imprimirlista);
		printf("Hay %d elementos en la lista", ft_lstsize(mini->lista));
}