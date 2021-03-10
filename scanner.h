/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 16:53:14 by tsierra-          #+#    #+#             */
/*   Updated: 2021/03/10 16:57:44 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCANNER_H
# define SCANNER_H

typedef struct s_token
{
	t_src	*src;
	int		len;
	char	*text;
}			t_token;

t_token	*tokenize(t_src *src);
void	free_token(t_token *tok);

#endif
