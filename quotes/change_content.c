/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_content.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 19:26:33 by tsierra-          #+#    #+#             */
/*   Updated: 2021/05/31 19:26:34 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_content(t_list *lst, void *content)
{
	void	*ptr;

	ptr = lst->content;
	lst->content = content;
	free(ptr);
}
