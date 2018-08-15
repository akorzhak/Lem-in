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

void	set_1st_levels(t_lem *l, t_room ***rooms)
{
	t_room **r;
	t_link *links;
	int 	level;

	r = *rooms;
	level = 1;
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
			r[dict(l, links->room1)]->level = level;
			r[dict(l, links->room2)]->level = level + 1;
		}
		else if (!ft_strcmp(links->room2, l->start_room))
		{
			r[dict(l, links->room2)]->level = level;
			r[dict(l, links->room1)]->level = level + 1;
		}
		links = links->next;
	}
}

void	set_levels(t_lem *l, t_room ***rooms)
{
	t_room **r;
	t_link *links;
	int 	level;
	char 	change;

	r = *rooms;
	set_1st_levels(l, rooms);
	do
	{
		change = 0;
		links = l->links;
		while (links)
		{
			if (ft_strcmp(links->room1, l->end_room)
				&& (level = r[dict(l, links->room1)]->level)
				&& !r[dict(l, links->room2)]->level)
			{
				r[dict(l, links->room2)]->level = level + 1;
				change = 1;
			}
			else if (ft_strcmp(links->room2, l->end_room)
				&& (level = r[dict(l, links->room2)]->level)
				&& !r[dict(l, links->room1)]->level)
			{
				r[dict(l, links->room1)]->level = level + 1;
				change = 1;
			}
			links = links->next;
		}
	} while (change);
}
