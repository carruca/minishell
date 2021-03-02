/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 16:02:41 by tsierra-          #+#    #+#             */
/*   Updated: 2021/03/01 16:19:19 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
	while (*s != c)
	{
		count++;
		s++;
	}
	return (count);
}

char		**ft_split(char const *s, char c)
{
	char	**table;
	int		word;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	word = 0;
	if (!(table = malloc(sizeof(char *) * ft_word_count(s, c) + 1)))
		return (NULL);
	while (word < ft_word_count(s, c))
	{
		if (!(table[word] = malloc(sizeof(char) * ft_strnlen(&s[i], c) + 1)))
			return (NULL);
		j = 0;
		while (s[i] == c)
			i++;
		while (s[i] != c && s[i])
			table[word][j++] = s[i++];
		table[word++][j] = '\0';
	}
	table[word] = NULL;
	return (table);
}
