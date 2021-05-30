#include "../minishell.h"

int	set_var(char *name, char *value, t_list **env_lst, int (*f)())
{
	t_list	*lst;	
	
	lst = ft_lstfind(*env_lst, name, env_name_cmp);
	if (!lst)
		init_var(name, value, env_lst);
	else if (f)
		f(value, lst->content);
	return (1);
}
