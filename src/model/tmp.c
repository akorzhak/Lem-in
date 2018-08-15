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
