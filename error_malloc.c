/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_malloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccardozo <ccardozo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 12:59:57 by ccardozo          #+#    #+#             */
/*   Updated: 2021/06/10 13:00:16 by ccardozo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft/libft.h"

void	error_malloc(void)
{
	ft_putstr_fd("Error malloc", 2);
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}
