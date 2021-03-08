#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct	s_nodo
{
	char	*nombre;
	char	*valor;
}	t_campo;

typedef struct	s_control
{
	t_list	*inicio;
	t_list	*fin;
	int	contador;
} t_control;

typedef struct	s_all
{
	int		exit;
	int		fd;
	char	*line;
	t_control *control;
	t_list	*lista;
	int		prueba;
}				t_all;

//Se encuentran en la carpeta srcs/
void	capture_env(t_all *mini, char **env);
void	insertardatos(t_campo **datos, char *str);

#endif
