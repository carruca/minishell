/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 14:58:27 by tsierra-          #+#    #+#             */
/*   Updated: 2021/03/10 16:47:04 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

size_t	get_delimiter_in_str(char *str, char delim)
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
		if (str[len] == delim && !quate[0] && !quate[1] && !quate[2])
		{
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
		if (compound[i] == ' ' && !quate[0] && !quate[1] && !quate[2])
			counter++;
		i++;
		quate[2] = 0;
	}
	return (counter);
}


void	split_compound_command(t_compound *compound)
{
	int		start;
	int		len;

	//Hacer tokens

	start = 0;
	len = 0;

	compound->token_counter = count_simple_command(compound->cmd);
	printf("counter = %d\n", compound->token_counter);
	compound->simple = malloc(sizeof(t_simple) * (compound->token_counter + 1));
	while (compound->cmd[start] != '\0')
	{
//		len = get_delimiter_in_str(&compound->cmd[start], ' ');
	/*	//buscar pipes redirecciones
		if (compound->cmd[len] == '|')
			compound->simple->control = PIPE;
		else if (compound->cmd[len] == '<')
			compound.simple->control = LESS;
		else if (compound->cmd[len] == '>')
			compound.control = GREAT;
		else if (compound->cmd[len] == '>' )*/
//		compound->cmd.simple->cmd = ft_substr(&compound->cmd[start], 0, len);
//		printf("simple command = %s", compound->cmd->simple->cmd);
//		start += len;
		start++;
	}
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
		len = get_delimiter_in_str(&line[start], ';');
		compound.cmd = ft_substr(&line[start], 0, len);
		printf("compound command = $%s$\n", compound.cmd);
		split_compound_command(&compound);
		free(compound.cmd);
		compound.cmd = NULL;
		start += len;
	}
}
