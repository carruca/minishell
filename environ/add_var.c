#include "../minishell.h"

int	add_var(t_var *var, t_list **env_lst)
{
	t_list	*new_lst;

	new_lst = ft_lstnew(var);
	if (!new_lst)
		return (0);
	ft_lstadd_back(env_lst, new_lst);
	return (1);
}
