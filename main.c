#include "minishell.h"

void	prompt_write()
{
	write(1, "minishell$ ", 11);
}

int	main()
{
	char	*line;

	line = NULL;
	prompt_write();
	while (get_next_line(0, &line) > 0)
	{
		printf("%s\n", line);
		free(line);
		prompt_write();
	}
	printf("%s\n", line);
	free(line);
	return (0);
}
