/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_steps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 17:24:05 by akorzhak          #+#    #+#             */
/*   Updated: 2018/07/02 17:24:07 by akorzhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	display_ways_capacity(t_ways **ways)
{
	int		i;
	t_ways	*w;

	i = 0;
	w = *ways;

	red();
	ft_putstr("\nWAYS' CAPACITIES:\n\n");
	reset();
	while (w)
	{
		printf("%d way: ", ++i);
			printf("%d\n", w->capacity_nb);
		w = w->next;
	}
	ft_putchar('\n');
}

void	display_valid_ways(t_ways **ways)
{
	int		i;
	t_ways	*w;

	w = *ways;
	yellow();
	ft_putstr("\nVALID WAYS:\n\n");
	reset();
	while (w)
	{
		i = 0;
		ft_putstr(w->rooms[i++]->name);
		while (w->rooms[i])
			ft_printf("->%s", w->rooms[i++]->name);
		w = w->next;
		ft_putchar('\n');
	}
}

void	display_adjacency_list(t_room ***rooms)
{
	int		i;
	t_room	**r;
	t_linkage *linked_rooms;

	i = 0;
	r = *rooms;
	green();
	ft_putstr("\nADJACENCY LIST:\n\n");
	reset();
	while (r[i])
	{
		linked_rooms = r[i]->linked_rooms;
		ft_putstr(r[i]->name);
		while (linked_rooms)
		{
			ft_printf("->%s", linked_rooms->room->name);
			linked_rooms = linked_rooms->next;
		}
		ft_putchar('\n');
		i++;
	}
}

void	display_bfs(t_room ***rooms)
{
	int		i;
	t_room	**r;

	i = 0;
	r = *rooms;
	blue();
	ft_putstr("BREADTH FIRST SEARCH:\n\n");
	reset();
	while (r[i])
	{
		ft_printf("room: %s ", r[i]->name);
		ft_printf("level: %d\n", r[i]->level);
		i++;
	}
}

void	display_all_steps(t_room ***rooms, t_ways **ways)
{
	display_bfs(rooms);
	display_adjacency_list(rooms);
	display_valid_ways(ways);
	display_ways_capacity(ways);
}