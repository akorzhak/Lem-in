/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 17:24:05 by akorzhak          #+#    #+#             */
/*   Updated: 2018/07/02 17:24:07 by akorzhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int 	line_nb = 1;

t_turn 	*record_step(char *room, int ant)
{
	t_turn *step;

	step = (t_turn *)ft_memalloc(sizeof(t_turn));
	step->room = ft_strdup(room);
	step->ant = ant;
	return (step);
}

void	add_step_to_turns(t_turn ***turns, char *room, int ant)
{
	static t_turn **t; //maybe not static
	static t_turn *step;

	t = *turns;
	if (t[line_nb])
	{
		step->next = record_step(room, ant);
		step = step->next;
	}
	else
	{
		t[line_nb] = record_step(room, ant);
		step = t[line_nb];
	}
}

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

void	free_the_link(t_link **links)
{
	ft_strdel(&(*links)->room1);
	ft_strdel(&(*links)->room2);
	ft_memdel((void **)links);
}

void	drop_the_link(t_lem *l, t_link **links)
{
	t_link *temp;

	temp = l->links;
	if (temp == (*links))
	{
		temp = temp->next;
		free_the_link(links);
		(*links) = temp;
	}
	else
	{
		while (temp->next && temp->next != (*links))
			temp = temp->next;
		if ((*links)->next == NULL)
		{
			temp->next = NULL;
			free_the_link(links);
		}
		else
		{
			temp->next = temp->next->next;
			free_the_link(links);
			(*links) = temp->next;
		}
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

void	set_linkages(t_lem *l, t_room ***rooms)
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

void	define_nb_of_transfers(t_way **ways)
{
	int len;
	t_way 	*w;

	len = 0;
	w = *ways;
	while (w)
	{
		while (w->rooms[len])
			len++;
		w->len = --len;
		w = w->next;
	}
}

void	define_ways_capacity(t_way **ways, t_lem *l)
{
	t_way 	*w;
	int 	turns;
	int 	sum_ants;
	int 	difference;

	turns = 1;
	define_nb_of_transfers(ways);
	if (l->ways_nb == 1)
	{
		(*ways)->capacity_nb = l->ants_nb;
		return ;
	}
	do
	{
		w = (*ways);
		sum_ants = 0;
		while (w)
		{
			w->capacity_nb = turns - w->len + 1;
			sum_ants += w->capacity_nb;
			w = w->next;
		}
		difference = l->ants_nb - sum_ants;
		turns += ft_ceil(difference, l->ways_nb);
	} while (difference > 0);
	if (difference < 0)
	{
		w = (*ways);
		while (w && difference)
		{
			w->capacity_nb--;
			difference++;
			w = w->next;
		}
	}
	l->turns = turns;
}

void	move_ants(t_lem *l, t_way **ways, t_turn ***turns)
{
	int n;
	int ant;
	int tmp;
	int temp;
	t_way *w;

	ant = 0;
	line_nb = 0;
	*turns = (t_turn **)ft_memalloc(sizeof(t_turn *) * (l->turns + 1));
	while (line_nb < l->turns)
	{
		w = *ways;
		while (w)
		{	
			n = 1;
			tmp = 0;
			if (w->rooms[n]->ant)
			{
				tmp = w->rooms[n]->ant;
				w->rooms[n]->ant = 0;
			}
			if (w->capacity_nb)
			{
				w->rooms[n]->ant = ++ant;
				w->capacity_nb--;
				add_step_to_turns(turns, w->rooms[n]->name, w->rooms[n]->ant);
			}
			n++;
			while (w->rooms[n])
			{
				temp = 0;
				if (w->rooms[n]->ant)
					temp = w->rooms[n]->ant;
				if ((w->rooms[n]->ant = tmp))
					add_step_to_turns(turns, w->rooms[n]->name, w->rooms[n]->ant);
				tmp = 0;
				if (w->rooms[++n])
				{
					if (w->rooms[n]->ant)
					{
						tmp = w->rooms[n]->ant;
						w->rooms[n]->ant = 0;
					}
					if ((w->rooms[n]->ant = temp))
						add_step_to_turns(turns, w->rooms[n]->name, w->rooms[n]->ant);
				}
				else
					break ;
				n++;
			}
			w = w->next;
		}
		line_nb++;
	}
}
