#include "minishell.h"

char	*ft_strjoin_free(char *dst, char *src)
{
	char	*tmp;

	tmp = dst;
	dst = ft_strjoin(dst, src);
	free(tmp);
	return (dst);
}
