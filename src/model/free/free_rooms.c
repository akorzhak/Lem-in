/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_rooms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 17:14:31 by akorzhak          #+#    #+#             */
/*   Updated: 2018/07/02 17:14:34 by akorzhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	free_linkages(t_linkage *linked_rooms)
{
	t_linkage	*next;

	while (linked_rooms)
	{
		next = linked_rooms->next;
		linked_rooms->room = NULL;
		linked_rooms->next = NULL;
		ft_memdel((void **)&linked_rooms);
		linked_rooms = next;
	}
}

void	free_rooms(t_room ***rooms)
{
	int		i;
	t_room	**r;

	i = 0;
	r = *rooms;
	if (rooms && *rooms)
	{
		while (r[i])
		{
			free_linkages((r[i])->linked_rooms);
			i++;
		}
		i = 0;
		while (r[i])
		{
			ft_strdel(&(r[i])->name);
			ft_memdel((void **)&r[i]);
			i++;
		}
		ft_memdel((void **)rooms);
	}
}
