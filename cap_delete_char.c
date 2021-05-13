#include "minishell.h"

void	cap_delete_char(t_env *_env)
{
	t_line	*line;
	char	*tmp;

	tmp = NULL;
	line = _env->cli->content;
	if (_env->len_cursor)
	{
		tputs(cursor_left, 1, ft_putchar);
		tputs(tgetstr("dm", 0), 1, ft_putchar);
		tputs(tgetstr("dc", 0), 1, ft_putchar);
		tputs(tgetstr("ed", 0), 1, ft_putchar);
		_env->cmd_cursor--;
		_env->cli_bufflen--;
		_env->len_cursor--;
		*_env->cmd_cursor = '\0';
		if (*(line->origin_line))
		{
			if (line->clone_line != NULL)
				tmp = line->clone_line;
			line->clone_line = ft_strdup(_env->cmd_buff);
			if (tmp)
				free(tmp);
		}
	}
	else
		tputs(tgetstr("te", 0), 1, ft_putchar);
}
