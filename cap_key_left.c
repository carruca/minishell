#include "minishell.h"

int	cap_key_left(t_cap *cap)
{	
	if (cap->len_cursor)
	{
		tputs(cursor_left, 1, ft_putchar);
		cap->len_cursor--;
	}
	ft_bzero(cap->ch, sizeof(cap->ch));
	cap->check_esc = 0;
	return (0);
}
