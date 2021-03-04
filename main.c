#include "minishell.h"

void	prompt_write()
{
	write(1, "minishell$ ", 11);
}

int	main()
{
	char	*line;

	line = NULL;
	while (1)
	{
		prompt_write();
		get_next_line(0, &line);
		printf("%s\n", line);
		if (!ft_strcmp(line, "exit"))
		{
			free(line);
			exit(0);
		}
		free(line);
	}
	return (0);
}
