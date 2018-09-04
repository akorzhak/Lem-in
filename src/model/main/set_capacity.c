/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_capacity.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 06:06:11 by akorzhak          #+#    #+#             */
/*   Updated: 2018/06/25 06:31:46 by akorzhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

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

void	allocate_ants(t_way **ways, int *difference, t_lem *l)
{
	int 	turns;
	int 	sum_ants;
	t_way 	*w;

	w = (*ways);
	turns = 1;
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
		*difference = l->ants_nb - sum_ants;
		turns += ft_ceil(*difference, l->ways_nb);
	} while (*difference > 0);
	l->turns = turns;
}

void	reduce_capacity(int difference, t_way **ways)
{
	t_way 	*w;

	w = (*ways);
	while (w && difference)
	{
		w->capacity_nb--;
		difference++;
		w = w->next;
	}
}

void	set_ways_capacity(t_way **ways, t_lem *l)
{
	int 	difference;

	define_nb_of_transfers(ways);
	if (l->ways_nb == 1)
	{
		(*ways)->capacity_nb = l->ants_nb;
		return ;
	}
	allocate_ants(ways, &difference, l);
	if (difference < 0)
		reduce_capacity(difference, ways);
}