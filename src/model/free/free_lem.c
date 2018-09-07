/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 17:14:31 by akorzhak          #+#    #+#             */
/*   Updated: 2018/07/02 17:14:34 by akorzhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	free_map(t_map **m)
{
	t_map	*map;
	t_map	*next;

	map = *m;
	while (map)
	{
		ft_strdel(&map->line);
		next = map->next;
		ft_memdel((void **)&map);
		map = next;
	}
}

void	free_lem(t_lem *l)
{
	if (l->start_room)
	{
		ft_strdel(&l->start_room);
	}
	if (l->end_room)
	{
		ft_strdel(&l->end_room);
	}
	if (l->e_message)
	{
		ft_strdel(&l->e_message);
	}
	if (l->map)
	{
		free_map(&l->map);
	}
	if (l->links)
	{
		free_links(&l->links);
	}
}
