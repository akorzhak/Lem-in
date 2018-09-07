/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_links.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 06:06:11 by akorzhak          #+#    #+#             */
/*   Updated: 2018/06/25 06:31:46 by akorzhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		link_the_rooms(t_room ***r, int i, char *linked_room)
{
	t_linkage	*linked_rooms;
	t_room		**rooms;

	rooms = *r;
	linked_rooms = rooms[i]->linked_rooms;
	if (!linked_rooms)
	{
		if (!(linked_rooms = (t_linkage *)ft_memalloc(sizeof(t_linkage))))
			return (MALLOC_ERROR);
		rooms[i]->linked_rooms = linked_rooms;
	}
	else
	{
		while (linked_rooms->next)
			linked_rooms = linked_rooms->next;
		if (!(linked_rooms->next = (t_linkage *)ft_memalloc(sizeof(t_linkage))))
			return (MALLOC_ERROR);
		linked_rooms = linked_rooms->next;
	}
	linked_rooms->room = rooms[dict(linked_room)];
	return (OK);
}

int		connect_rooms(t_lem *l, t_link **links, t_room **rooms, int i)
{
	if (!ft_strcmp(rooms[i]->name, (*links)->room1))
	{
		if (link_the_rooms(&rooms, i, (*links)->room2) == MALLOC_ERROR)
		{
			l->e_message = ft_strdup(MALLOC_FAIL);
			return (MALLOC_ERROR);
		}
	}
	else if (!ft_strcmp(rooms[i]->name, (*links)->room2))
	{
		if (link_the_rooms(&rooms, i, (*links)->room1) == MALLOC_ERROR)
		{
			l->e_message = ft_strdup(MALLOC_FAIL);
			return (MALLOC_ERROR);
		}
	}
	return (OK);
}

int		set_links(t_lem *l, t_room ***r)
{
	int		i;
	t_link	*links;
	t_room	**rooms;

	rooms = *r;
	i = 0;
	while (rooms[i])
	{
		links = l->links;
		while (links)
		{
			while (links && ft_strcmp(rooms[i]->name, links->room1)
						&& ft_strcmp(rooms[i]->name, links->room2))
				links = links->next;
			if (!links)
				break ;
			if (connect_rooms(l, &links, rooms, i) == MALLOC_ERROR)
				return (ERROR);
			links = links->next;
		}
		i++;
	}
	return (OK);
}
