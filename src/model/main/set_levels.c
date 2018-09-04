/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_levels.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 17:24:05 by akorzhak          #+#    #+#             */
/*   Updated: 2018/07/02 17:24:07 by akorzhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	set_1st_levels(t_lem *l, t_room ***r)
{
	t_link *links;
	t_room	**rooms;

	rooms = *r;
	links = l->links;
	while (links)
	{
		while (links && ft_strcmp(links->room1, l->start_room)
			&& ft_strcmp(links->room2, l->start_room))
			links = links->next;
		if (!links)
			return ;
		if (!ft_strcmp(links->room1, l->start_room))
		{
			rooms[dict(l, links->room1)]->level = 1;
			rooms[dict(l, links->room2)]->level = 2;
		}
		else if (!ft_strcmp(links->room2, l->start_room))
		{
			rooms[dict(l, links->room2)]->level = 1;
			rooms[dict(l, links->room1)]->level = 2;
		}
		links = links->next;
	}
}

int		set_level(t_lem *l, t_room ***r, t_link *links)
{
	int 	level;
	t_room	**rooms;

	rooms = *r;
	if (ft_strcmp(links->room1, l->end_room)
		&& (level = rooms[dict(l, links->room1)]->level)
		&& !rooms[dict(l, links->room2)]->level)
	{
		rooms[dict(l, links->room2)]->level = level + 1;
		return (1);
	}
	else if (ft_strcmp(links->room2, l->end_room)
		&& (level = rooms[dict(l, links->room2)]->level)
		&& !rooms[dict(l, links->room1)]->level)
	{
		rooms[dict(l, links->room1)]->level = level + 1;
		return (1);
	}
	return (0);
}

int		set_levels(t_lem *l, t_room ***rooms)
{
	t_link *links;
	char 	change;
	t_room	**r;

	r = *rooms;
	set_1st_levels(l, rooms);
	do
	{
		change = 0;
		links = l->links;
		while (links)
		{
			change = set_level(l, rooms, links);
			links = links->next;
		}
	} while (change);
	if ((r[dict(l, l->start_room)]->level == 0)
		|| (r[dict(l, l->end_room)]->level == 0))
	{
		l->e_message = ft_strdup(NO_WAY);
		return (ERROR);
	}
	return (OK);
}
