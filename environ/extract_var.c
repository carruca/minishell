#include "../minishell.h"

void	extract_var(char **str, char **name, char **value)
{
	char	*pos;

	pos = ft_strchr(*str, '=');
	if (!pos)
		*name = *str;
	else
	{
		*pos = '\0';
		*name = *str;
		*value = pos + 1;
	}
}
