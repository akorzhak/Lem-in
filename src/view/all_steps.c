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

void	display_ways_capacity(t_way **ways)
{
	int		i;
	t_way	*w;

	i = 0;
	w = *ways;
	red();
	underline();
	ft_putstr(CAPACITY);
	reset();
	while (w)
	{
		ft_printf("%d way: ", ++i);
		ft_printf("%d\n", w->capacity_nb);
		w = w->next;
	}
	ft_putchar('\n');
}

void	display_valid_ways(t_way **ways)
{
	int		i;
	t_way	*w;

	w = *ways;
	yellow();
	underline();
	ft_putstr(VALID_WAYS);
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

void	display_adjacency_list(t_room **rooms)
{
	int			i;
	t_linkage	*linked_rooms;

	i = 0;
	green();
	underline();
	ft_putstr(ADJ_LIST);
	reset();
	while (rooms[i])
	{
		linked_rooms = rooms[i]->linked_rooms;
		ft_putstr(rooms[i]->name);
		while (linked_rooms)
		{
			ft_printf("->%s", linked_rooms->room->name);
			linked_rooms = linked_rooms->next;
		}
		ft_putchar('\n');
		i++;
	}
}

void	display_bfs(t_room **rooms)
{
	int		i;

	i = 0;
	blue();
	underline();
	ft_putstr(BFS);
	reset();
	while (rooms[i])
	{
		ft_printf("room: %s ", rooms[i]->name);
		ft_printf("level: %d\n", rooms[i]->level);
		i++;
	}
}

void	display_map(t_map *map)
{
	while (map)
	{
		ft_printf("%s\n", map->line);
		map = map->next;
	}
	ft_putchar('\n'); //???????
}
