#include "minishell.h"

t_line	*next_line_key_aux(t_cap *cap)
{
	t_line	*line;

	create_node(cap);
	cap->cli_bufflen = 0;
	while (cap->cli->prev)
	{
		line = cap->cli->content;
		cap->cli = cap->cli->prev;
	}
	return (line);
}

char	*next_line_key(t_cap *cap)
{
	t_line	*line;

	line = cap->cli->content;
	write(1, "\n", 1);
	if (*cap->cmd_buff)
	{
		line = next_line_key_aux(cap);
		if (cap->cli->next->content)
		{
			line = cap->cli->next->content;
			free(line->clone_line);
			return (line->origin_line);
		}
	}	
	else
	{
		while (cap->cli->prev)
		{
			line = cap->cli->content;
			cap->cli = cap->cli->prev;
		}
		return ("");
	}
	return (NULL);
}
