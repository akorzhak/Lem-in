/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rooms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 17:24:05 by akorzhak          #+#    #+#             */
/*   Updated: 2018/07/02 17:24:07 by akorzhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		handle_commands(char *line, int *property)
{
	if (ft_strstr(line, "##start"))
	{
		if (*property)
			return (ERROR);
		*property = ENTRANCE;
	}
	else if (ft_strstr(line, "##end"))
	{
		if (*property)
			return (ERROR);
		*property = EXIT;
	}
	return (OK);
}

int		get_rooms(t_lem *l, t_room ***rooms, char **line)
{
	int			property;
	t_namelist	*names;

	property = ORDINARY;
	names = NULL;
	while (get_next_line(0, line) > 0 && !ft_strchr(*line, '-'))
	{
		if ((save_map_line(l, *line) == OK) && **line == '#')
		{
			if (handle_commands(*line, &property) == ERROR)
				return (exit_with_error(l, line, MULTIPLE_START_END_ROOM));
			ft_strdel(line);
			continue ;
		}
		if (record_name(line, &names, property, l) == ERROR)
			return (ERROR);
		ft_strdel(line);
		property = ORDINARY;
		l->rooms_nb++;
	}
	if (!l->start_room || !l->end_room)
		return (exit_with_error(l, line, NO_START_END_ROOM));
	if (form_adj_list(l, rooms, names) == ERROR)
		return (exit_with_error(l, line, MALLOC_FAIL));
	return (OK);
}
