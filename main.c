#include "minishell.h"

void	print_prompt()
{
	ft_putstr_fd("minishell$ ", 1);
}

char	*read_line()
{
	char *line;

	if (get_next_line(0, &line) < 0)
	{
		ft_putstr_fd("error", 2);
	}
	return (line);
}

int	main()
{
	char	*cmd;

	cmd = NULL;
	while (1)
	{
		print_prompt();
		get_next_line(0, &cmd);
		printf("%s\n", cmd);
		if (!ft_strcmp(cmd, "exit"))
		{
			free(cmd);
			exit(0);
		}
		free(cmd);
	}
	return (0);
}
