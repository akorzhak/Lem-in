/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   form_adj_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 17:24:05 by akorzhak          #+#    #+#             */
/*   Updated: 2018/07/02 17:24:07 by akorzhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		form_adj_list(t_lem *l, t_room ***rooms, t_namelist *names)
{
	int			i;
	t_namelist	*head;
	t_room		**r;

	i = 0;
	head = names;
	if (!(r = (t_room **)ft_memalloc(sizeof(t_room *) * (l->rooms_nb + 1))))
		return (ERROR);
	while (i < l->rooms_nb)
	{
		if (!(r[i] = (t_room *)ft_memalloc(sizeof(t_room))))
			return (ERROR);
		if (!((r[i])->name = ft_strdup(names->name)))
			return (ERROR);
		(r[i])->property = names->property;
		names = names->next;
		i++;
	}
	r[i] = NULL;
	*rooms = r;
	free_namelist(&head);
	return (OK);
}
