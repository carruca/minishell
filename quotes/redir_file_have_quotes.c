#include "../minishell.h"

int	redir_file_have_quotes(char **str, t_shell *sh)
{
	char	*new;
	char	*ptr;

	if (str[0][0] == '$')
	{
		print_error(sh, *str, "ambiguous redirect", 1);
		return (0);
	}
	else if (ft_strchr(*str, '\'') || ft_strchr(*str, '\"') || ft_strchr(*str, '$'))
	{
		new = trim_quotes(*str, sh);
		ptr = *str;
		*str = new;
		free(ptr);
	}
	return (1);
}
