/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccardozo <ccardozo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 16:02:41 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/11 16:58:45 by ccardozo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static char	*ft_word(char const *s, char c, int i)
{
	char	*word;
	int		o;
	int		p;

	p = i;
	while (p >= 0 && s[p] != c)
		p--;
	o = i - p;
	word = (char *)malloc(sizeof(char) * (o + 1));
	p = i;
	while (p > 0 && s[p - 1] != c)
		p--;
	o = 0;
	while (p <= i)
	{
		word[o] = s[p];
		o++;
		p++;
	}
	word[o] = '\0';
	return (word);
}

static void	ft_clean(char **str, int a)
{
	int		i;

	i = 0;
	while (i < a)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char		**ft_split(char const *s, char c)
{
	char	**result;
	int		i;
	int		j;

	if (!s ||
			!(result = (char **)malloc(sizeof(char *) * (ft_count(s, c) + 1))))
		return (0);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
		{
			result[j] = ft_word(s, c, i);
			if (result[j] == NULL)
			{
				ft_clean(result, j);
				return (0);
			}
			j++;
		}
		i++;
	}
	result[j] = NULL;
	return (result);
}
