#include "libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>

int	execute(int i, char **argv, char **env, int fd_in, int *fd_next)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		if (fd_in)
		{
			printf("hijo %i: Proceso encadenado, duplicando fd_in(%i) a stdin\n", i, fd_in);
			dup2(fd_in, 0);
		}
		else
			printf("hijo %i: Proceso inicial, asumimos que fd_in es 0\n", i);
		printf("hijo %i: Cerrando fd_next de lectura, puesto que nosotros solo vamos a escribir al siguiente proceso\n", i);
		close(fd_next[0]);
		if (fd_next[1] != 1)
		{
			printf("hijo %i: Duplicamos fd_next[1] a 1, para mandar la salida al siguiente proceso\n", i);
			dup2(fd_next[1], 1);
		}
		else
			printf("hijo %i: Este es el ultimo proceso, asumimos que fd_next[1] es 1\n", i);
		printf("hijo %i: Ejecutamos execve('%s', argv, env);\n", i, argv[0]);
		execve(argv[0], argv, env);
		close(fd_next[1]);
		exit(0);
	}
	else
	{
		if (fd_in)
		{
			printf("padre: fd_in no es 0, cerrando\n");
			close(fd_in);
		}
		if (fd_next[1] != 1)
			close(fd_next[1]);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	int		fd_in;
	int		fd_next[2];
	int		i;

	i = 1;
	fd_in = 0;
	while (i < argc)
	{
		if (argv[i + 1])
			pipe(fd_next);
		else
			fd_next[1] = 1;
		execute(i, ft_split(argv[i], ' '), env, fd_in, fd_next);
		fd_in = fd_next[0];
		i++;
	}
	while (--i)
		printf("Proceso %i, finalizado\n", wait(NULL));
//	system("lsof -c pipe");
	return (0);
}
