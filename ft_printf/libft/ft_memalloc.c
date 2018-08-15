/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 11:31:41 by akorzhak          #+#    #+#             */
/*   Updated: 2017/11/03 11:31:44 by akorzhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void *arr;

	if ((arr = (void*)malloc(sizeof(void) * size)) == NULL)
	{
		ft_putstr("Memory allocation failed.\n")
		exit(EXIT_FAILURE);
	}
	ft_bzero(arr, size);
	return (arr);
}
