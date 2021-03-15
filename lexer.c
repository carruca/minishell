/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 14:58:27 by tsierra-          #+#    #+#             */
/*   Updated: 2021/03/15 19:41:49 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

size_t	get_delimiter_in_str(char *str, char *set)
{
	size_t		len;
	unsigned	quate[3];

	len = 0;
	ft_bzero(quate, sizeof(quate));
	while (str[len] != '\0' && *str)
	{
		if (str[len] == '\\' && !quate[0] && !quate[1])
		{
			len++;
			quate[2] = 1;
		}
		if (str[len] == '\"' && !quate[0])
			quate[1] = quate[1] ^ 1;
		if (str[len] == '\'' && !quate[1])
			quate[0] = quate[0] ^ 1;
		if (ft_strchr(set, str[len]) && !quate[0] && !quate[1] && !quate[2])
		{
			len++;
			if (ft_strchr(set, str[len]))
				len++;
			break ;
		}
		len++;
		quate[2] = 0;
	}
	return (len);
}

int		count_simple_command(char *compound)
{
	int	counter;
	int	i;
	int	quate[3];

	counter = 1;
	i = 0;
	ft_bzero(quate, sizeof(quate));
	while (compound[i] != '\0')
	{
		if (compound[i] == '\\' && !quate[0] && !quate[1])
		{
			i++;
			quate[2] = 1;
		}
		if (compound[i] == '\"' && !quate[0] && !quate[2])
			quate[1] = quate[1] ^ 1;
		if (compound[i] == '\'' && !quate[1] && !quate[2])
			quate[0] = quate[0] ^ 1;
		if (ft_strchr("<>|", compound[i]) && !quate[0] && !quate[1] && !quate[2])
		{
			if (compound[i + 1] == '>')
				i++;
			counter++;
		}
		i++;
		quate[2] = 0;
	}
	return (counter);
}


void	split_compound_command(t_compound *compound)
{
	int		start;
	int		len;
	char	*tmp;
	int		i;

	i = 0;
	start = 0;
	len = 0;
	compound->simple_counter = 0;
	tmp = ft_strtrim(compound->cmd, " ;");
	compound->simple_counter = count_simple_command(tmp);
	printf("tmp = $%s$\n", tmp);
	printf("counter = %d\n", compound->simple_counter);
	compound->simple = ft_calloc(compound->simple_counter, sizeof(t_simple));
//	compound->simple[compound->token_counter] = NULL;
//	printf("%lu\n", sizeof(t_simple));
	while (tmp[start] != '\0')
	{
		len = get_delimiter_in_str(tmp + start, "<>|");
		printf("len token = %d\n", len);
		compound->simple[i].cmd = ft_substr(tmp + start, 0, len);
		printf("simple command = %s\n", compound->simple[i].cmd);
		free(compound->simple[i].cmd);
		i++;
		start += len;
	}
	free(tmp);
	free(compound->simple);
}

void	split_command_line(char *line)
{
	t_compound	compound;
	int			start;
	int			len;

	start = 0;
	len = 0;
	ft_bzero(&compound, sizeof(compound));
	while (line[start] != '\0')
	{
		len = get_delimiter_in_str(line + start, ";");
		compound.cmd = ft_substr(line, start, len);
		printf("compound command = $%s$\n", compound.cmd);
		split_compound_command(&compound);
		free(compound.cmd);
		compound.cmd = NULL;
		start += len;
	}
}
