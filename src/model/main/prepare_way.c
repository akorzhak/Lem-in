/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_way.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 06:06:11 by akorzhak          #+#    #+#             */
/*   Updated: 2018/06/25 06:31:46 by akorzhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	choose_next_room(t_linkage **link, int len, char *start_room)
{
	while (*link && ((*link)->room->level != len
		|| ((*link)->room->used
		&& ft_strcmp((*link)->room->name, start_room))))
	{
		*link = (*link)->next;
	}
}

int		add_next_room(t_linkage **link, char ***w, int len, char *start_room)
{
	char **way;

	way = *w;
	while (len)
	{
		choose_next_room(link, len, start_room);
		if (!*link)
			break ;
		if (!(way[--len] = ft_strdup((*link)->room->name)))
		{
			clean_way(w, len);
			return (MALLOC_ERROR);
		}
		(*link)->room->used = TRUE;
		*link = (*link)->room->linked_rooms;
	}
	return (OK);
}

int		prepare_way(t_lnk *lnk, char ***way, t_i *i, t_lem *l)
{
	char **w;

	i->len = lnk->p_room->room->level + 2;
	i->lenth = i->len;
	if (!(w = (char **)ft_memalloc(sizeof(char *) * i->len--)))
		return (MALLOC_ERROR);
	if (!(w[--i->len] = ft_strdup(l->end_room)))
	{
		ft_memdel((void **)&w);
		return (MALLOC_ERROR);
	}
	i->last_room_index = i->len;
	if (!(w[--i->len] = ft_strdup(lnk->p_room->room->name)))
	{
		clean_way(&w, i->len);
		return (MALLOC_ERROR);
	}
	lnk->p_room->room->used = TRUE;
	lnk->link = lnk->p_room->room->linked_rooms;
	if (add_next_room(&lnk->link, &w, i->len, l->start_room) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	*way = w;
	return (OK);
}
