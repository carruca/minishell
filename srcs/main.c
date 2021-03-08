#include "../include/minishell.h"

void	prompt_write()
{
	write(1, "minishell$ ", 11);
}

int	main(int argc, char *argv[], char **env)
{
	t_all	mini;
	char *argumento;

	capture_env(&mini, env);
	mini.line = NULL;
	mini.prueba = argc;
	argumento = argv[1];
	while (1)
	{
		prompt_write();
		get_next_line(0, &mini.line);
		printf("%s", mini.line);
		if (!ft_strcmp(mini.line, "exit"))
		{
			free(mini.line);
			exit(0);
		}
		free(mini.line);
		//ft_memset(mini.line, 0, ft_strlen(mini.line));
	}
	return (0);
}
