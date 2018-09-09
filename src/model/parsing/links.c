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

static int	validate_link(t_lem *l, char **arr, char **line)
{
	int	i_room1;
	int	i_room2;

	if (arrlen(arr) != 2)
		return (exit_with_error(l, line, INCOMPLETE_LINK_DATA));
	i_room1 = dict(arr[0]);
	i_room2 = dict(arr[1]);
	if (i_room1 == -1)
		return (exit_with_error(l, line, ft_strjoin(INVALID_ROOM, arr[0])));
	if (i_room2 == -1)
		return (exit_with_error(l, line, ft_strjoin(INVALID_ROOM, arr[1])));
	if (i_room1 == i_room2)
		return (exit_with_error(l, line, SELF_LINKED_ROOM));
	return (OK);
}

int			validate_and_save(t_lem *l, char **line)
{
	char	**arr;

	if (has_chr(*line, ' ') || count_chr(*line, '-') != 1)
		return (exit_with_error(l, line, INVALID_FORMAT_LINK));
	arr = ft_strsplit(*line, '-');
	if (validate_link(l, arr, line) == ERROR)
	{
		free_2darray(&arr);
		ft_strdel(line);
		return (ERROR);
	}
	save_link(l, arr[0], arr[1]);
	free_2darray(&arr);
	ft_strdel(line);
	return (OK);
}

int			get_links(t_lem *l, char **line)
{
	int	gnl;

	gnl = 1;
	if (!*line)
		return (exit_with_error(l, line, NO_LINKS));
	while (gnl > 0)
	{
		gnl = 0;
		if (save_map_line(l, *line) == MALLOC_ERROR)
			return (exit_with_error(l, line, MALLOC_FAIL));
		if (**line == '#')
		{
			if (ft_strnstr(*line, "##", 2))
				return (exit_with_error(l, line, IRRELEVANT_COMMAND));
			ft_strdel(line);
			gnl = get_next_line(0, line);
			continue ;
		}
		if (validate_and_save(l, line) == ERROR)
			return (ERROR);
		gnl = get_next_line(0, line);
	}
	ft_strdel(line);
	return (OK);
}
