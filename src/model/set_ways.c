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

void	prepare_way(t_lnk *lnk, char ***way, t_i *i, t_lem *l)
{
	char **w;

	i->len = lnk->penultimate_room->room->level + 2;
	i->lenth = i->len;
	w = (char **)ft_memalloc(sizeof(char *) * i->len--);
	w[--i->len] = ft_strdup(l->end_room);
	i->last_room_index = i->len;
	w[--i->len] = ft_strdup(lnk->penultimate_room->room->name);
	lnk->penultimate_room->room->used = USED;
	lnk->link = lnk->penultimate_room->room->linked_rooms;
	while (i->len)
	{
		while (lnk->link && (lnk->link->room->level != (i->len)
			|| (lnk->link->room->used
			&& ft_strcmp(lnk->link->room->name, l->start_room))))
		{
			lnk->link = lnk->link->next;
		}
		if (!lnk->link)
			break ;
		w[--i->len] = ft_strdup(lnk->link->room->name);
		lnk->link->room->used = USED;
		lnk->link = lnk->link->room->linked_rooms;
	}
	*way = w;
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
	while ((lnk.penultimate_room =
		choose_penultimate_room(&(rooms[i.i]->linked_rooms))))
	{
		prepare_way(&lnk, &way, &i, l);
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
