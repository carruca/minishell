/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 16:02:41 by tsierra-          #+#    #+#             */
/*   Updated: 2021/03/04 15:27:01 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	ft_word_count(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else
		{
			count++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
	}
	return (count);
}

static int	ft_strnlen(char const *s, char c)
{
	int	count;

	count = 0;
	while (s[count] != c && s[count] != '\0')
		count++;
	return (count);
}

static int	ft_tablecpy(char const *s, char **table, char c)
{
	int		word;
	int		i;
	int		j;

	word = 0;
	i = 0;
	j = 0;
	while (word < ft_word_count(s, c))
	{
		table[word] = malloc(sizeof(char) * ft_strnlen(&s[i], c) + 1);
		if (!table[word])
			return (0);
		j = 0;
		while (s[i] == c)
			i++;
		while (s[i] != c && s[i])
			table[word][j++] = s[i++];
		table[word++][j] = '\0';
	}
	table[word] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**table;

	if (!s)
		return (NULL);
	table = malloc(sizeof(char *) * ft_word_count(s, c) + 1);
	if (!table)
		return (NULL);
	if (!ft_tablecpy(s, table, c))
		return (NULL);
	return (table);
}
