/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 14:48:46 by akorzhak          #+#    #+#             */
/*   Updated: 2017/11/29 14:48:49 by akorzhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				free_gnl_remainders(void)
{
	t_dlist *next;

	while (dlist)
	{
		next = (dlist)->next;
		ft_strdel(&dlist->buff);
		ft_memdel((void **)&dlist);
		dlist = next;
	}
}
