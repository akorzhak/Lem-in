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
	if ((set_levels(l, rooms) == ERROR) || (set_links(l, rooms) == ERROR))
		return (ERROR);
	if (pave_the_ways(&ways, l, *rooms) == ERROR)
	{
		free_ways(&ways);
		return (ERROR);
	}
	set_ways_capacity(&ways, l);
	print_handled_data(l, *rooms, &ways);
	if (move_ants(l, &ways, &turns) == MALLOC_ERROR)
	{
		free_ways(&ways);
		return (ERROR);
	}
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
		ft_strdel(&line);
		return (ERROR);
	}
	init_dict(l->rooms_nb, *rooms);
	if (get_links(l, &line) == ERROR || validate_dict(l) == ERROR)
	{
		free_dict();
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
	init_lemin(&l);
	g_line_nb = 1;
	if (argc <= 3 && (handle_args(argc, argv, &l) == OK))
	{
		if ((parsing_controller(&l, &rooms) == ERROR)
			|| (program_logic_controller(&l, &rooms) == ERROR))
		{
			display_error_message(&l);
			free_lem(&l);
			free_rooms(&rooms);
			return (ERROR);
		}
		free_all(&l, &rooms);
		return (OK);
	}
	display_usage_message();
	return (ERROR);
}
