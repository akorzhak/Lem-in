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

#include "lemin.h"

void	define_nb_of_transfers(t_way **ways)
{
	int		len;
	t_way	*w;

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

/*
** Function uses author algorithm for defining each way's capacity.
**
** @turns denotes the number of all turns needed to pass the farm.
**		(a row with simultaneous steps)
** @one_more is a special case flag, when summary pseudo capacity is
**		equal to real ants number, but contains at least one negative capacity.
**		If @one_more is TRUE - program recalculates ways' capacity.
**
** The program initially assumes, that it is possible to pass it in one turn.
** Then it calculates pseudo capacity for ways (it can be negative).
** Thereafter program finds the difference between real ants number
** and summary pseudo capacity.
**
** Being based on mentioned difference, program calculates true number
** of turns and new capacities.
** Gotten summary capacity can a bit exceed total number of ants.
** In this case the program evenly reduces capacities.
*/

void	allocate_ants(t_way **ways, int *difference, t_lem *l)
{
	char	one_more;
	int		turns;
	int		sum_ants;
	t_way	*w;

	w = (*ways);
	turns = 1;
	one_more = TRUE;
	while (*difference > 0 || one_more)
	{
		w = (*ways);
		sum_ants = 0;
		one_more = FALSE;
		while (w)
		{
			w->capacity_nb = turns - w->len + 1;
			(w->capacity_nb < 0) ? one_more = TRUE : 0;
			sum_ants += w->capacity_nb;
			w = w->next;
		}
		*difference = l->ants_nb - sum_ants;
		turns += ceil_div(*difference, l->ways_nb);
	}
	l->turns = turns;
}

/*
** In case summary rooms' capacity exceeds total number
** of ants - following funcion equalizes mentioned values.
*/

void	reduce_capacity(int difference, t_way **ways)
{
	t_way *w;

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
	int difference;

	difference = TRUE;
	define_nb_of_transfers(ways);
	allocate_ants(ways, &difference, l);
	if (difference < 0)
		reduce_capacity(difference, ways);
}
