/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 17:31:56 by akorzhak          #+#    #+#             */
/*   Updated: 2018/07/05 17:31:58 by akorzhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	display_result(t_turn ***turns)
{
	t_turn	**t;
	t_turn	*step;
	int 	n;

	t = *turns;
	n = 0;
	while (t[n])
	{
		step = t[n];
		while (step)
		{
			printf("L%d-%s ", step->ant, step->room);
			step = step->next;
		}
		n++;
		printf("\n");
	}
}

void	print_handled_data(t_lem *l, t_room ***rooms, t_way **ways)
{
	display_map(l->map);
	if (l->a)
	{
		display_bfs(rooms);
		display_adjacency_list(rooms);
		display_valid_ways(ways);
		display_ways_capacity(ways);
	}
}
