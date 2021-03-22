/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 14:58:27 by tsierra-          #+#    #+#             */
/*   Updated: 2021/03/17 18:37:01 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

int		isquated(char c)
{
	static int	quated = 0;

	if (c == '\'')
		quated ^= 0x01;
	else if (c == '\"')
		quated ^= 0x02;
	return (quated);
}

size_t	skip_to_delimiter(char *str, char *set)
{
	size_t	len;
	int		quated;

	len = 0;
	quated = 0;
	while (str[len] != '\0' && *str)
	{
/*		if (str[len] == '\"' && (quated == 0 || quated == 0x02))
			quated ^= 0x02;
		else if (str[len] == '\'' && (quated == 0 || quated == 0x01))
			quated ^= 0x01;*/
		quated = isquated(str[len]);
		if (ft_strchr(set, str[len]) && !quated)
		{
			len++;
			if (str[len - 1] == str[len])
				len++;
			break ;
		}
		len++;
	}
	return (len);
}

size_t	get_delimiter_in_str(char *str, char *set)
{
	size_t			len;
	unsigned char	quates;

	len = 0;
	quates = 0;
	while (str[len] != '\0' && *str)
	{
		if (str[len] == '\"' && (quates == 0 || quates == 0x02))
			quates ^= 0x02;
		else if (str[len] == '\'' && (quates == 0 || quates == 0x01))
			quates ^= 0x01;
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
		if (compound[i] == '\"' && (quates == 0 || quates == 0x02))
			quates ^= 0x02;
		else if (compound[i] == '\'' && (quates == 0 || quates == 0x01))
			quates ^= 0x01;
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

void	split_simple_command(t_simple *simple, char **simple_command)
{
	int		i;
	char	*tmp;
	int		start;
	int		len;

	i = 0;
	start = 0;
	len = 0;
	tmp = NULL;
	tmp = ft_strtrim(*simple_command, " ");
	printf("simple simple = %s\n", tmp);
	simple->token_counter = count_simple_command(tmp, " ");
	printf("token counter = %d\n", simple->token_counter);
	simple->token_vector = ft_calloc(simple->token_counter,
			sizeof (char *));
	while (i < simple->token_counter)
	{
		len = get_delimiter_in_str(tmp + start, " ");
		simple->token_vector[i] = ft_substr(tmp, start, len);
		printf("token = %s\n", simple->token_vector[i]);
		free(simple->token_vector[i]);
		i++;
		start += len;
	}
	free(simple->token_vector);
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
	compound->simple = ft_calloc(compound->simple_counter, sizeof (t_simple));
	while (tmp[start] != '\0')
	{
		len = get_delimiter_in_str(tmp + start, "<>|");
		printf("len simple command = %d\n", len);
		compound->simple[i].cmd = ft_substr(tmp, start, len);
		printf("simple command = $%s$\n", compound->simple[i].cmd);
		split_simple_command(compound->simple, &compound->simple[i].cmd);
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
		len = skip_to_delimiter(line + start, ";");
		compound.cmd = ft_substr(line, start, len);
		printf("compound command = $%s$\n", compound.cmd);
		split_compound_command(&compound);
		free(compound.cmd);
		compound.cmd = NULL;
		start += len;
	}
}
