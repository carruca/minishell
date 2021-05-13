#include "minishell.h"

void	free_node(t_lista *node)
{
	t_line	*line;

	line = node->content;
	free(line->origin_line);
	free(line->clone_line);
	free(line);
}
