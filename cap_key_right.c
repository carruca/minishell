#include "minishell.h"

int	cap_key_right(t_cap *cap)
{
	if (cap->cmd_buff[cap->len_cursor])
	{
		tputs(cursor_right, 1, ft_putchar);
		cap->len_cursor++;
	}
	ft_bzero(cap->ch, sizeof(cap->ch));
	cap->check_esc = 0;
	return (0);
}
