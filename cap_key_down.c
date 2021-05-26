#include "minishell.h"

int	cap_key_down(t_cap *cap)
{
	if (cap->cli->prev)
	{
		cap->cli = cap->cli->prev;
		find_history(cap);
	}
	ft_bzero(cap->ch, sizeof(cap->ch));
	cap->check_esc = 0;
	return (0);
}
