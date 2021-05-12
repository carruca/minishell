#include "minishell.h"

void	cap_delete_char(t_env *lst_env)
{
	t_line	*line;

	line = lst_env->cli->content;
	if (lst_env->cli_bufflen > 0)
	{
		tputs(cursor_left, 1, ft_putchar);
		tputs(tgetstr("dm", 0), 1, ft_putchar);
		tputs(tgetstr("dc", 0), 1, ft_putchar);
		tputs(tgetstr("ed", 0), 1, ft_putchar);
		lst_env->cmd_cursor--;
		lst_env->cli_bufflen--;
		lst_env->len_cursor--;
		*lst_env->cmd_cursor = '\0';
		if (*(line->origin_line))
			line->clone_line = ft_strdup(lst_env->cmd_buff);
	}
	else
		tputs(tgetstr("te", 0), 1, ft_putchar);
}
