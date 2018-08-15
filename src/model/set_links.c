/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_links.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 06:06:11 by akorzhak          #+#    #+#             */
/*   Updated: 2018/06/25 06:31:46 by akorzhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	link_the_rooms(t_lem *l, t_room ***rooms, int i, char *linked_room)
{
	t_room **r;
	t_linkage *linked_rooms;

	r = *rooms;
	linked_rooms = r[i]->linked_rooms;
	if (!linked_rooms)
	{
		linked_rooms = (t_linkage *)ft_memalloc(sizeof(t_linkage));
		r[i]->linked_rooms = linked_rooms;
	}
	else
	{
		while (linked_rooms->next)
			linked_rooms = linked_rooms->next;
		linked_rooms->next = (t_linkage *)ft_memalloc(sizeof(t_linkage));
		linked_rooms = linked_rooms->next;
	}
	linked_rooms->room = r[dict(l, linked_room)];
}

void	set_links(t_lem *l, t_room ***rooms)
{
	int 	i;
	t_room **r;
	t_link *links;

	i = 0;
	r = *rooms;
	while(r[i])
	{
		links = l->links;
		while (links)
		{
			while (links && ft_strcmp(r[i]->name, links->room1)
						&& ft_strcmp(r[i]->name, links->room2))
				links = links->next;
			if (!links)
				break ;
			if (!ft_strcmp(r[i]->name, links->room1))
				link_the_rooms(l, rooms, i, links->room2);
			else if (!ft_strcmp(r[i]->name, links->room2))
				link_the_rooms(l, rooms, i, links->room1);
			links = links->next;
		}
		i++;
	}
}
