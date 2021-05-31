#include "./minishell.h"

void	args_have_quotes(t_list *lst, t_shell *sh)
{
	char	*new;
	char	*str;

	while (lst)
	{
		str = lst->content;
		if (ft_strchr(str, '\'') || ft_strchr(str, '\"') || ft_strchr(str, '$'))
		{
			new = trim_quotes(str, sh);
			change_content(lst, new);
		}
		lst = lst->next;
	}
}
