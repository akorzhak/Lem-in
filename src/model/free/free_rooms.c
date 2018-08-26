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

void	free_rooms(t_room ***rooms) //FAIL TO DO!!!!!!!!!!!!!
{
	int	i;
	t_linkage	*linked_rooms;
	t_linkage	*next;

	i = 0;
	if (rooms && *rooms)
	{
		while (*rooms[i])
		{
	 		linked_rooms = (*rooms[i])->linked_rooms;
	// 		ft_strdel(&((*rooms[i])->name));
	// 		ft_printf("2\n");
	 		while (linked_rooms)
	 		{
				ft_printf("3\n");
				next = linked_rooms->next;
				linked_rooms->room = NULL;
				linked_rooms->next = NULL; //?????
	 			ft_memdel((void **)&linked_rooms);
	 			linked_rooms = next;
	 		}
	// 		ft_printf("4\n");
	// 		ft_memdel((void **)rooms[i]);
	// 		ft_printf("5\n");
			i++;
		}
	// 	printf("6\n");
	// 	ft_memdel((void **)rooms);
	}
}