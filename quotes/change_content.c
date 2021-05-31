#include "../minishell.h"

void	change_content(t_list *lst, void *content)
{
	void	*ptr;

	ptr = lst->content;
	lst->content = content;
	free(ptr);
}
