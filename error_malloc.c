#include "env.h"

void	error_malloc()
{
	ft_putstr_fd("Error malloc", 2);
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}
