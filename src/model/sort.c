/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 17:24:05 by akorzhak          #+#    #+#             */
/*   Updated: 2018/07/02 17:24:07 by akorzhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

/**
uses bubble sort
returns 0 if list unsorted;
1 - if sorted
*/
int 	is_sorted_list(t_turn *list)
{
	while (list && list->next)
	{
		if (list->ant > list->next->ant)
			return (0);
		list = list->next;
	}
	return (1);
}

void 	select_prior_step(t_turn **loop, t_turn **prior, t_turn **prev)
{
	t_turn	*step;
	t_turn  *temp;

	temp = 0;
	*prev = 0;
	step = *loop;
	*prior = step;
	while (step)
	{
		if (step->ant < (*prior)->ant)
		{
			*prev = temp;
			*prior = step;
		}
		temp = step;
		step = step->next;
	}
}

void	add_step_to_sorted_part(t_turn  **sort, t_turn  **prior)
{
	if (*sort)
	{
		(*sort)->next = *prior;
		*sort = (*sort)->next;
	}
	else
	{
		*sort = *prior;
	}
}


void	set_pointers(t_turn **loop, t_turn **prior, t_turn **prev)
{
	if (*prev)
		(*prev)->next = (*prior)->next;
	if (*prior == *loop)
		*loop = (*loop)->next;
	(*prior)->next = *loop;
}

/**
uses selection sort
*/
void	sort_result(t_turn ***turns)
{
	t_turn	**t;
	t_sort 	s;
	int 	i;

	t = *turns;
	i = 0;
	while (t[i])
	{
		if (is_sorted_list(t[i]))
		{
			i++;
			continue ;
		}
		s.loop = t[i];
		s.sort = 0;
		while (s.loop->next)
		{
			select_prior_step(&s.loop, &s.prior, &s.prev);
			set_pointers(&s.loop, &s.prior, &s.prev);	
			if (!s.sort)
				t[i] = s.prior;
			add_step_to_sorted_part(&s.sort, &s.prior);
		}
		i++;
	}
}
