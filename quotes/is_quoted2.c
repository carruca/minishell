#include "../minishell.h"

void	is_quoted_2(char c, int *quoted, int *i)
{
	if (c == '\"' && (*quoted == 0 || *quoted == 0x01))
	{
		*quoted ^= 0x01;
		(*i)++;
	}
	else if (c == '\'' && (*quoted == 0 || *quoted == 0x02))
	{
		*quoted ^= 0x02;
		(*i)++;
	}
}
