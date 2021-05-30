#include "../minishell.h"

int	init_var(char *name, char *value, t_list **env_lst)
{
	t_var	*var;

	var = ft_calloc(1 , sizeof(t_var));
	if (!var)
		return (1);
	var->name = ft_strdup(name);
	if (!var->name)
		return (1);
	if (value != NULL)
		var->value = ft_strdup(value);
	set_flags(var);
	add_var(var, env_lst);
	if (!var)
		return (1);
	return (0);
}
