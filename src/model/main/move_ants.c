/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 17:24:05 by akorzhak          #+#    #+#             */
/*   Updated: 2018/07/02 17:24:07 by akorzhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_turn	*record_step(char *room, int ant)
{
	t_turn *step;

	step = (t_turn *)ft_memalloc(sizeof(t_turn));
	step->room = ft_strdup(room);
	step->ant = ant;
	return (step);
}

void	add_step_to_turns(t_turn ***turns, char *room, int ant)
{
	t_turn			**t;
	static t_turn	*step;

	t = *turns;
	if (t[g_line_nb])
	{
		step->next = record_step(room, ant);
		step = step->next;
	}
	else
	{
		t[g_line_nb] = record_step(room, ant);
		step = t[g_line_nb];
	}
}

void	let_the_ant_move(t_way **ways, t_ints *i, t_turn ***turns)
{
	t_way *w;

	w = *ways;
	if (w->rooms[i->n]->ant)
	{
		i->tmp = w->rooms[i->n]->ant;
		w->rooms[i->n]->ant = 0;
	}
	if (w->capacity_nb)
	{
		w->rooms[i->n]->ant = ++i->ant;
		w->capacity_nb--;
		add_step_to_turns(turns, w->rooms[i->n]->name, w->rooms[i->n]->ant);
	}
	i->n++;
}

int		relocate_moving_ants(t_way **ways, t_ints *i, t_turn ***turns)
{
	t_way *w;

	w = *ways;
	i->temp = 0;
	if (w->rooms[i->n]->ant)
		i->temp = w->rooms[i->n]->ant;
	if ((w->rooms[i->n]->ant = i->tmp))
		add_step_to_turns(turns, w->rooms[i->n]->name, w->rooms[i->n]->ant);
	i->tmp = 0;
	if (w->rooms[++i->n])
	{
		if (w->rooms[i->n]->ant)
		{
			i->tmp = w->rooms[i->n]->ant;
			w->rooms[i->n]->ant = 0;
		}
		if ((w->rooms[i->n]->ant = i->temp))
			add_step_to_turns(turns, w->rooms[i->n]->name, w->rooms[i->n]->ant);
	}
	else
		return (0);
	i->n++;
	return (1);
}

int		move_ants(t_lem *l, t_way **ways, t_turn ***turns)
{
	t_ints	i;
	t_way	*w;

	i.ant = 0;
	g_line_nb = 0;
	if (!(*turns = (t_turn **)ft_memalloc(sizeof(t_turn *) * (l->turns + 1))))
		return (MALLOC_ERROR);
	while (g_line_nb < l->turns)
	{
		w = *ways;
		while (w)
		{
			i.n = 1;
			i.tmp = 0;
			let_the_ant_move(&w, &i, turns);
			while (w->rooms[i.n])
			{
				if (!relocate_moving_ants(&w, &i, turns))
					break ;
			}
			w = w->next;
		}
		g_line_nb++;
	}
	return (OK);
}
