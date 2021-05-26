/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_malloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccardozo <ccardozo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 18:02:39 by ccardozo          #+#    #+#             */
/*   Updated: 2021/05/26 18:03:07 by ccardozo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	error_malloc(void)
{
	ft_putstr_fd("Error malloc", 2);
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}
