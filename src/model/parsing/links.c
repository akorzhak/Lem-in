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

int 	validate_link(t_lem *l, char **arr, char **line)
{
	int 	i_room1;
	int 	i_room2;

	if (arrlen(arr) != 2)
		return (exit_with_error(l, line, INCOMPLETE_LINK_DATA));
	i_room1 = dict(l, arr[0]);
	i_room2 = dict(l, arr[1]);
	if (i_room1 == -1)
		return (exit_with_error(l, line, ft_strjoin(INVALID_ROOM, arr[0])));
	if (i_room2 == -1)
		return (exit_with_error(l, line, ft_strjoin(INVALID_ROOM, arr[1])));
	if (i_room1 == i_room2)
		return (exit_with_error(l, line, SELF_LINKED_ROOM));
	return (OK);
}

int 	get_links(t_lem *l, char **line)
{
	char	**arr;

	if (!*line)
		return (exit_with_error(l, line, NO_LINKS));
	do
	{
		if (**line == '#')
		{
			if (ft_strstr(*line, "##start") || ft_strstr(*line, "##end"))
				return (exit_with_error(l, line, IRRELEVANT_COMMAND));
			save_map_line(l, *line);
			continue ;
		}
		save_map_line(l, *line);
		if (has_spaces(*line))
			return (exit_with_error(l, line, SPACES));
		arr = ft_strsplit(*line, '-');
		if (validate_link(l, arr, line) == ERROR)
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
