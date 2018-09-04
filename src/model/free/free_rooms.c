/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_rooms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 17:14:31 by akorzhak          #+#    #+#             */
/*   Updated: 2018/07/02 17:14:34 by akorzhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	free_rooms(t_room ***rooms)
{
	int	i;
	t_room		**r;
	t_linkage	*linked_rooms;
	t_linkage	*next;

	i = 0;
	r = *rooms;
	if (rooms && *rooms)
	{
		while (r[i])
		{
	 		linked_rooms = (r[i])->linked_rooms;
	 		while (linked_rooms)
	 		{
				next = linked_rooms->next;
				linked_rooms->room = NULL;
				linked_rooms->next = NULL;
	 			ft_memdel((void **)&linked_rooms);
	 			linked_rooms = next;
	 		}
			i++;
		}
		i = 0;
		while (r[i])
		{
			ft_strdel(&(r[i])->name);
			ft_memdel((void **)&r[i]);
			i++;
		}
 		ft_memdel((void **)rooms);
	}
}
