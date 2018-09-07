/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ways.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 17:14:31 by akorzhak          #+#    #+#             */
/*   Updated: 2018/07/02 17:14:34 by akorzhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	clean_way(char ***w, int len)
{
	char **way;

	way = *w;
	while (way[++len])
		ft_strdel(w[len]);
	ft_memdel((void **)w);
}

void	drop_the_way(char ***way, int i)
{
	char **w;

	w = *way;
	while (w[i])
		ft_strdel(&w[i--]);
	ft_memdel((void **)way);
}

void	free_ways(t_way **ways)
{
	t_way	*w;
	t_way	*next;
	int		i;

	w = *ways;
	while (w)
	{
		i = 0;
		next = w->next;
		while (w->rooms[i])
		{
			ft_strdel(&(w->rooms[i]->name));
			ft_memdel((void **)&(w->rooms[i]));
			i++;
		}
		ft_memdel((void **)&(w->rooms));
		ft_memdel((void **)&w);
		w = next;
	}
}
