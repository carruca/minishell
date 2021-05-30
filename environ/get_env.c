#include "../minishell.h"

char	*get_env(char *name, t_list *env_lst)
{
	t_list	*lst;

	lst = ft_lstfind(env_lst, name, env_name_cmp);
	if (!lst)
		return (NULL);
	return (((t_var *)(lst->content))->value);
}
