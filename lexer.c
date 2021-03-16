/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 14:58:27 by tsierra-          #+#    #+#             */
/*   Updated: 2021/03/16 16:30:53 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

size_t	get_delimiter_in_str(char *str, char *set)
{
	size_t			len;
	unsigned char	quates;

	len = 0;
	quates = 0;
	while (str[len] != '\0' && *str)
	{
		if (str[len] == '\"' && (quates == 0 || quates == 0x2))
			quates ^= 0x2;
		else if (str[len] == '\'' && (quates == 0 || quates == 0x1))
			quates ^= 0x1;
		else if (ft_strchr(set, str[len]) && !quates)
		{
			len++;
			if (str[len - 1] == '>' && str[len] == '>')
				len++;
			break ;
		}
		else if (str[len] == '\\' && !quates)
			len++;
		len++;
	}
	return (len);
}

int	count_simple_command(char *compound, char *set)
{
	int				counter;
	int				i;
	unsigned char	quates;

	counter = 1;
	i = 0;
	quates = 0;
	while (compound[i] != '\0')
	{
		if (compound[i] == '\"' && (quates == 0 || quates == 0x2))
			quates ^= 0x2;
		else if (compound[i] == '\'' && (quates == 0 || quates == 0x1))
			quates ^= 0x1;
		else if (ft_strchr(set, compound[i]) && !quates)
		{
			if (compound[i] == '>' && compound[i + 1] == '>')
				i++;
			counter++;
		}
		else if (compound[i] == '\\' && !quates)
			i++;
		i++;
	}
	return (counter);
}

void	split_simple_command(t_simple *simple)
{
//	char	*token;
	char	*tmp;
	int		start;
	int		len;

	start = 0;
	len = 0;
	tmp = NULL;
	tmp = ft_strtrim(simple->cmd, " ");
	printf("simple simple = %s\n", tmp);
	simple->token_counter = count_simple_command(tmp, " ");
	printf("token counter = %d\n", simple->token_counter);
//	simple->argv = 
	while (tmp[start] != '\0')
	{
		len = get_delimiter_in_str(tmp, " ");
		start += len;
	}
	free(tmp);
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
	tmp = NULL;
	tmp = ft_strtrim(compound->cmd, " ;");
	compound->simple_counter = count_simple_command(tmp, "<>|");
	printf("compound compound = $%s$\n", tmp);
	printf("simple counter = %d\n", compound->simple_counter);
	compound->simple = ft_calloc(compound->simple_counter, sizeof(t_simple));
	while (tmp[start] != '\0')
	{
		len = get_delimiter_in_str(tmp + start, "<>|");
		printf("len simple command = %d\n", len);
		compound->simple[i].cmd = ft_substr(tmp, start, len);
		printf("simple command = %s\n", compound->simple[i].cmd);
		split_simple_command(compound->simple);
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
