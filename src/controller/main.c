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

int 	program_logic_controller(t_lem *l, t_room ***rooms)
{
	t_way	*ways;
	t_turn	**turns;

	set_levels(l, rooms);
	set_links(l, rooms);
	pave_the_ways(&ways, l, rooms);
	set_ways_capacity(&ways, l);
	print_handled_data(l, rooms, &ways);
	move_ants(l, &ways, &turns);
	sort_result(&turns);
	display_result(&turns);
	return (OK);
}

int 	parsing_controller(t_lem *l, t_room ***rooms)
{
	char	*line;

	line = NULL;
	*rooms = NULL;
	if (get_ants(l) == ERROR || get_rooms(l, rooms, &line) == ERROR)
	{
		display_error_message(l);
		free_lem(l);
		ft_strdel(&line);
		return (ERROR);
	}
	init_dict(l, *rooms);
	if (get_links(l, &line) == ERROR)
	{
		display_error_message(l);
		free_dict();
		free_lem(l);
		ft_strdel(&line);
		return (ERROR);
	}
	return (OK);
}

int		main(int argc, char **argv)
{
	t_lem	l;
	t_room	**rooms;

	if (argc <= 3)
	{
		init_lemin(&l);
		if (handle_args(argc, argv, &l) == ERROR)
			return (display_usage_message());
		if (parsing_controller(&l, &rooms) == ERROR)
			return (ERROR);
		if (program_logic_controller(&l, &rooms) == ERROR)
			return (ERROR);
		return (OK);
	}
	display_usage_message();
	return (ERROR);
}
