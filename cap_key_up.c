#include "minishell.h"

int	cap_key_up(t_cap *cap)
{
	if (cap->cli->next)
	{
		cap->cli = cap->cli->next;
		find_history(cap);
	}
	ft_bzero(cap->ch, sizeof(cap->ch));
	cap->check_esc = 0;
	return (0);
}
