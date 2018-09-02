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

t_way 	*ways;

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

int		add_way_to_list(char ***way, int lenth)
{
	char **w;

	w = *way;
	if (!w[0])
		return (ERROR);
	if (ways->rooms)
	{
		if (!(ways->next = (t_way *)ft_memalloc(sizeof(t_way))))
			return (MALLOC_ERROR);
		ways = ways->next;
	}
	if (!(ways->rooms = (t_ant_room **)ft_memalloc(sizeof(t_ant_room *) * lenth--)))
		return (MALLOC_ERROR);
	while (lenth--)
	{
		if (!(ways->rooms[lenth] = (t_ant_room *)ft_memalloc(sizeof(t_ant_room))))
			return (MALLOC_ERROR);
		if (!(ways->rooms[lenth]->name = ft_strdup(w[lenth])))
			return (MALLOC_ERROR);
	}
	return (OK);
}

int		pave_the_ways(t_way **w, t_lem *l, t_room **rooms)
{
	t_i 	i;
	t_lnk 	lnk;
	char	**way;
	int		res;

	i.i = 0;
	*w = (t_way *)ft_memalloc(sizeof(t_way));
	ways = *w;
	while (ft_strcmp(rooms[i.i]->name, l->end_room))
		i.i++;
	rooms[i.i]->used = USED;
	while ((lnk.p_room = choose_penultimate_room(&(rooms[i.i]->linked_rooms))))
	{
		if (prepare_way(&lnk, &way, &i, l) == MALLOC_ERROR)
			return (ERROR);
		res = add_way_to_list(&way, i.lenth);
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
