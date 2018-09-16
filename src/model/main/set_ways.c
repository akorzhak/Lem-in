/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_ways.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 06:06:11 by akorzhak          #+#    #+#             */
/*   Updated: 2018/06/25 06:31:46 by akorzhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_linkage	*choose_penultimate_room(t_linkage **linked_rooms)
{
	int			lowest_lvl;
	t_linkage	*rooms;
	t_linkage	*penultimate_room;

	lowest_lvl = 0;
	rooms = *linked_rooms;
	penultimate_room = NULL;
	while (rooms)
	{
		if ((!lowest_lvl || rooms->room->level < lowest_lvl)
			&& (rooms->room->used == FALSE) && rooms->room->level)
		{
			lowest_lvl = rooms->room->level;
			penultimate_room = rooms;
		}
		rooms = rooms->next;
	}
	return (penultimate_room);
}

int			add_way_to_list(t_way **ways, char ***way, int len)
{
	char			**w;
	static t_way	*ws;

	if (!ws)
		ws = *ways;
	w = *way;
	if (!w[0])
		return (ERROR);
	if (ws->rooms)
	{
		if (!(ws->next = (t_way *)ft_memalloc(sizeof(t_way))))
			return (MALLOC_ERROR);
		ws = ws->next;
	}
	if (!(ws->rooms = (t_ant_room **)ft_memalloc(sizeof(t_ant_room *) * len--)))
		return (MALLOC_ERROR);
	while (len--)
	{
		if (!(ws->rooms[len] = (t_ant_room *)ft_memalloc(sizeof(t_ant_room))))
			return (MALLOC_ERROR);
		if (!(ws->rooms[len]->name = ft_strdup(w[len])))
			return (MALLOC_ERROR);
	}
	return (OK);
}

int			pave_the_ways(t_way **w, t_lem *l, t_room **rooms)
{
	t_i		i;
	t_lnk	lnk;
	char	**way;
	int		res;

	i.i = 0;
	*w = (t_way *)ft_memalloc(sizeof(t_way));
	while (ft_strcmp(rooms[i.i]->name, l->end_room))
		i.i++;
	rooms[i.i]->used = TRUE;
	while ((lnk.p_room = choose_penultimate_room(&(rooms[i.i]->linked_rooms))))
	{
		if (prepare_way(&lnk, &way, &i, l) == MALLOC_ERROR)
			return (ERROR);
		res = add_way_to_list(w, &way, i.lenth);
		if (res == OK)
			free_2darray(&way);
		else if (res == ERROR)
			drop_the_way(&way, i.last_room_index);
		else if (res == MALLOC_ERROR)
			return (ERROR);
		l->ways_nb++;
	}
	return (OK);
}
