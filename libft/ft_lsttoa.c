#include "libft.h"

char	**ft_lsttoa(t_list *lst)
{
	char	**new;
	int		counter;
	int		i;
	
	counter = ft_lstsize(lst);
	new = ft_calloc(counter + 1, sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	while (i < counter)
	{
		new[i] = ft_strdup((char *)lst->content);
		if (!new[i])
		{
			ft_free_tab(new);
			return (NULL);
		}
		lst = lst->next;
		i++;
	}
	new[i] = NULL;
	return (new);
}
