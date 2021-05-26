#include "minishell.h"

void	cap_delete_char(t_cap *cap)
{
	t_line	*line;
	char	*tmp;

	tmp = NULL;
	line = cap->cli->content;
	if (cap->len_cursor)
	{
		tputs(cursor_left, 1, ft_putchar);
		tputs(tgetstr("dm", 0), 1, ft_putchar);
		tputs(tgetstr("dc", 0), 1, ft_putchar);
		tputs(tgetstr("ed", 0), 1, ft_putchar);
		cap->cmd_cursor--;
		cap->cli_bufflen--;
		cap->len_cursor--;
		*cap->cmd_cursor = '\0';
		if (*(line->origin_line))
		{
			if (line->clone_line != NULL)
				tmp = line->clone_line;
			line->clone_line = ft_strdup(cap->cmd_buff);
			if (tmp)
				free(tmp);
		}
	}
	else
	{
		free(line->clone_line);
		line->clone_line = NULL;
		tputs(tgetstr("te", 0), 1, ft_putchar);
	}
}
