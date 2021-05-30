#include "../minishell.h"

t_list	*extract_env(char **env)
{
	t_list	*env_lst;

	env_lst	= NULL;
	while (*env)
	{
		build_var(env, &env_lst, modify_value);
		env++;
	}
	return (env_lst);
}
