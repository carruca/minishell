#include "../minishell.h"

int	build_var(char **str, t_list **env_lst, int (*f)())
{
	char	*name;
	char	*value;

	name = NULL;
	value = NULL;
	extract_var(str, &name, &value);
	set_var(name, value, env_lst, f);
	restore_env(str);
	return (1);
}
