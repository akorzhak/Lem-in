/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 06:06:11 by akorzhak          #+#    #+#             */
/*   Updated: 2018/06/25 06:31:46 by akorzhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		program_logic_controller(t_lem *l, t_room ***rooms)
{
	t_way	*ways;
	t_turn	**turns;

	ways = NULL;
	turns = NULL;
	set_levels(l, rooms);
	if (set_links(l, rooms) == ERROR)
	{
		free_rooms(rooms);
		return (ERROR);
	}
	if (pave_the_ways(&ways, l, *rooms) == ERROR)
	{
		free_ways(&ways);
		free_rooms(rooms);
		return (ERROR);
	}
	set_ways_capacity(&ways, l);
	print_handled_data(l, *rooms, &ways);
	move_ants(l, &ways, &turns);
	sort_result(&turns);
	display_result(&turns);
	free_ways(&ways);
	free_turns(&turns);
	return (OK);
}

int		parsing_controller(t_lem *l, t_room ***rooms)
{
	char *line;

	line = NULL;
	if (get_ants(l) == ERROR || get_rooms(l, rooms, &line) == ERROR)
	{
		display_error_message(l);
		free_lem(l);
		free_rooms(rooms);
		ft_strdel(&line);
		return (ERROR);
	}
	init_dict(l, *rooms);
	if (get_links(l, &line) == ERROR)
	{
		display_error_message(l);
		free_all(l, rooms);
		ft_strdel(&line);
		return (ERROR);
	}
	return (OK);
}

int		main(int argc, char **argv)
{
	t_lem	l;
	t_room	**rooms;

	rooms = NULL;
	if (argc <= 3)
	{
		init_lemin(&l);
		if (handle_args(argc, argv, &l) == ERROR)
			return (display_usage_message());
		if (parsing_controller(&l, &rooms) == ERROR)
			return (ERROR);
		if (program_logic_controller(&l, &rooms) == ERROR)
			return (ERROR);
		free_all(&l, &rooms);
		return (OK);
	}
	display_usage_message();
	return (ERROR);
}
