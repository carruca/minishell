/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_new_lst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccardozo <ccardozo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 14:03:38 by ccardozo          #+#    #+#             */
/*   Updated: 2021/06/10 14:09:51 by ccardozo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// recibe una estructura t_var y crea un nodo de la lista

t_lista	*ft_dlstnew(void *content)
{
	t_lista	*new;

	new = NULL;
	new = malloc(sizeof(t_lista));
	if (!new)
		return (NULL);
	new->content = content;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}
