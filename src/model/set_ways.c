/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_ways.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 06:06:11 by akorzhak          #+#    #+#             */
/*   Updated: 2018/06/25 06:31:46 by akorzhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	drop_the_way(char ***way, int i)
{
	char **w;

	w = *way;
	while (w[i])
		ft_strdel(&w[i--]);
	// free(way);
	// way = NULL;
	ft_memdel((void **)*way);
}

t_linkage *choose_penultimate_room(t_linkage **linked_rooms)
{
	int 	lowest_lvl = 0;
	t_linkage 	*rooms;
	t_linkage 	*penultimate_room;

	rooms = *linked_rooms;
	penultimate_room = NULL;
	while (rooms)
	{
		if ((!lowest_lvl || rooms->room->level < lowest_lvl)
			&& (rooms->room->used == NOT_USED) && rooms->room->level)
		{
			lowest_lvl = rooms->room->level;
			penultimate_room = rooms;
		}
		rooms = rooms->next;
	}
	return (penultimate_room);
}

void	pave_the_ways(t_way **ways, t_lem *l, t_room ***rooms)
{
	int 	i;
	int 	len;
	int 	lenth;
	int 	last_room_index;
	t_room **r;
	t_linkage *penultimate_room;
	t_linkage *link;
	char	**way;
	t_way 	*w;
	int fl;

	i = 0;
	r = *rooms;
	*ways = (t_way *)ft_memalloc(sizeof(t_way));
	w = *ways;
	fl = 0;
	while (ft_strcmp(r[i]->name, l->end_room))
		i++;
	r[i]->used = USED;
	while ((penultimate_room = choose_penultimate_room(&(r[i]->linked_rooms))))
	{
		len = penultimate_room->room->level + 2;
		lenth = len;
		way = (char **)ft_memalloc(sizeof(char *) * len--);
		way[--len] = ft_strdup(l->end_room);
		last_room_index = len;
		way[--len] = ft_strdup(penultimate_room->room->name);
		penultimate_room->room->used = USED;
		link = penultimate_room->room->linked_rooms;
		while (len)
		{
			while (link && (link->room->level != (len + fl) || (link->room->used
				&& ft_strcmp(link->room->name, l->start_room))))
				link = link->next;
			if (!link)
				break ;
			way[--len] = ft_strdup(link->room->name);
			link->room->used = USED;
			link = link->room->linked_rooms;
		}
		if (!way[0])
		{
			drop_the_way(&way, last_room_index);
			break ;
		}
		if (w->rooms)
		{
			w->next = (t_way *)ft_memalloc(sizeof(t_way));
			w = w->next;
		}
		w->rooms = (t_ant_room **)ft_memalloc(sizeof(t_ant_room *) * lenth--);
		while (lenth--)
		{
			w->rooms[lenth] = (t_ant_room *)ft_memalloc(sizeof(t_ant_room));
			w->rooms[lenth]->name = ft_strdup(way[lenth]);
		}
		l->ways_nb++;
	}
}