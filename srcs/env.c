#include "../include/minishell.h"


void imprimirlista(void *cabeza)
{
	t_campo *nodo;
	nodo = (void *)cabeza;
	//printf("Nombre = %s \n", cabeza->nombre);
	//printf("Valor = %s \n", cabeza->valor);
	printf("Nombre = %s \n", nodo->nombre);
	printf("Valor = %s \n", nodo->valor);

}

void	capture_env(t_all *mini ,char **env)
{
	t_campo *datos;
	t_list	*aux;
	t_list	*head;

	datos = NULL;
	aux = NULL;
	mini->lista = NULL;
	datos = (t_campo *)malloc(sizeof(t_campo));
	while (*env)
	{
		insertardatos(&datos, *env);
		printf("%s \n", datos->nombre);
		printf("%s \n", datos->valor);
		mini->prueba = 1;
	
		env++;
		if (aux == NULL)
		{
			aux = ft_lstnew(datos);
			head = aux;
		}
		else
		{
			ft_lstadd_back(&aux, ft_lstnew(datos));
		}
	}
	mini->control->contador = ft_lstsize(aux);
	printf("Hay %d elementos en la lista\n", mini->control->contador);
}