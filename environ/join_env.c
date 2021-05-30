#include "../minishell.h"

char	*join_env(t_var	*var)
{
	return (ft_strjoin_btwchar(var->name, var->value, '='));
}
