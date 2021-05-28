#include "../minishell.h"

int	is_valid_var(char *str)
{
	if (!str || *str == '=')
		return (0);
	while (*str && *str != '=')
	{
		if (ft_isdigit(str[0]) || (!ft_isalnum(*str) && *str != '_'))
			return (0);
		str++;
	}
	if (*str == '=')
		return (2);
	return (1);
}
