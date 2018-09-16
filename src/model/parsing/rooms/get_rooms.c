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

#include "lemin.h"

int		handle_commands(t_lem *l, char **line, int *property)
{
	if (*property)
	{
		if (ft_strnstr(*line, "##", 2))
			return (exit_with_error(l, line, MULTIPLE_COMMANDS));
		return (exit_with_error(l, line, COMMENT_AFTER_COMMAND));
	}
	if (ft_strcmp(*line, "##start") == EQUAL)
	{
		*property = ENTRANCE;
	}
	else if (ft_strcmp(*line, "##end") == EQUAL)
	{
		*property = EXIT;
	}
	return (OK);
}

int		get_rooms(t_lem *l, t_room ***rooms, char **line)
{
	int			property;
	t_namelist	*n;

	property = ORDINARY;
	n = NULL;
	while (get_next_line(0, line) > 0 && (has_chr(*line, ' ') || **line == '#'))
	{
		if ((save_map_line(l, *line) == OK) && **line == '#')
		{
			if (handle_commands(l, line, &property) == ERROR)
				return (ERROR);
			ft_strdel(line);
			continue ;
		}
		if ((record_name(line, &n, property, l) == ERROR) && free_namelist(&n))
			return (ERROR);
		ft_strdel(line);
		property = ORDINARY;
		l->rooms_nb++;
	}
	if (!line && (!l->start_room || !l->end_room) && free_namelist(&n))
		return (exit_with_error(l, line, NO_START_END_ROOM));
	if ((form_adj_list(l, rooms, n) == ERROR) && free_namelist(&n))
		return (exit_with_error(l, line, MALLOC_FAIL));
	return (OK);
}
