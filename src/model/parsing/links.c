/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 17:24:05 by akorzhak          #+#    #+#             */
/*   Updated: 2018/07/02 17:24:07 by akorzhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int 	get_links(t_lem *l, char **line)
{
	char	**arr;
	int 	i_room1;
	int 	i_room2;

	do
	{
		if (**line == '#')
		{
			if (ft_strstr(*line, "##start") || ft_strstr(*line, "##end"))
				return (delete_line_and_exit(line));
			save_map_line(l, *line);
			continue ;
		}
		save_map_line(l, *line);
		arr = ft_strsplit(*line, '-');
		if (arrlen(arr) != 2)
		{
			l->e_message = ft_strdup(INCOMPLETE_LINK_DATA);
			free_2darray(&arr);
			return (ERROR);
		}
		i_room1 = dict(l, arr[0]);
		i_room2 = dict(l, arr[1]);
		if (i_room1 == -1)
			l->e_message = ft_strjoin(INVALID_ROOM, arr[0]);
		else if (i_room2 == -1)
			l->e_message = ft_strjoin(INVALID_ROOM, arr[1]);
		else if (i_room1 == i_room2)
			l->e_message = ft_strdup(SELF_LINKED_ROOM);
		if (i_room1 == -1 || i_room2 == -1 || i_room1 == i_room2)
		{
			free_2darray(&arr);
			return (ERROR);
		}
		save_link(l, arr[0], arr[1]);
		free_2darray(&arr);
		ft_strdel(line);
	} while (get_next_line(0, line) > 0);
	return (OK);
}