/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 17:24:05 by akorzhak          #+#    #+#             */
/*   Updated: 2018/07/02 17:24:07 by akorzhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	save_link(t_lem *l, char *room1, char *room2)
{
	static t_link *links;

	if (!l->links)
	{
		l->links = (t_link *)ft_memalloc(sizeof(t_link));
		links = l->links;
	}
	else
	{
		while (links->next)
			links = links->next;
		links->next = (t_link *)ft_memalloc(sizeof(t_link));
		links = links->next;
	}
	links->room1 = ft_strdup(room1);
	links->room2 = ft_strdup(room2);
}

t_map	*add_line_to_list(char *line)
{
	t_map *map;

	map = (t_map *)ft_memalloc(sizeof(t_map));
	map->line = ft_strdup(line);
	map->nb = line_nb++;
	return (map);
}

void	save_map_line(t_lem *l, char *line)
{
	static t_map 	*map;

	if (l->map)
	{
		map->next = add_line_to_list(line);
		map = map->next;
	}
	else
	{
		l->map = add_line_to_list(line);
		map = l->map;
	}
}
