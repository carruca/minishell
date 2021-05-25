#include "minishell.h"


// recibe un string y busca la palabra echo al principio
// si lo encuentra devuelve 0 de lo contrario devuelve 1
// --> esta función es solo para hacer pruebas

// int	find_builtin(char *cmd, char *builtin)
// {
// 	while (*builtin)
// 	{
// 		if (*cmd++ != *builtin++)
// 			return (1);
// 	}
// 	return (0);
// }

//funcion para cambiar el nivel de la shell
/*
void	set_shelllvl(t_env *_env)
{
	char	*value;
	int		level;
	
	value = find_node("SHLVL", _env->env_lst);
	level = ft_atoi(value) + 1;
	value = ft_itoa(level);
	set_env(_env->env_lst, "SHLVL", value);
}*/

//funcion para encontrar los comandos
//esta función es solo para hacer pruebas
/*
int	work_to_list(t_env *_env, char *cmd)
{
	char	**cmdline;
	int		len;

	if (cmd)
	{
		len = 0;
		cmdline = ft_split(cmd, ' ');
		while (cmdline[len])
			len++;
		if (cmdline[0] && (!ft_strcmp(cmdline[0], "./minishell") || !ft_strcmp(cmdline[0], "bash")))
			set_shelllvl(_env);
		execute_builtin(len, cmdline, _env);     //    <---- esta llamada a la funcion es la que tenemos que meter en un punto del parseo
		while (_env->env_lst && _env->env_lst->prev != NULL)	  // lo demas no sirve mas que para pruebas.
			_env->env_lst = _env->env_lst->prev;
		ft_free_tab(cmdline);
	}
	return (0);
}*/
