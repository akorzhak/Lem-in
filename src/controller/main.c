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

int 	handle_args(int argc, char **argv, t_lem *l)
{
	if (argc >= 2)
	{
		if (!ft_strcmp(argv[1], "-e"))
			l->e = 1;
		else if (!ft_strcmp(argv[1], "-a"))
			l->a = 1;
		else
			return (0);
		if (argc == 3)
		{
			if (!ft_strcmp(argv[2], "-e") && !l->e)
				l->e = 1;
			else if (!ft_strcmp(argv[2], "-a") && !l->a)
				l->a = 1;
			else
				return (0);
		}
	}
	return (1);
}

int		main(int argc, char **argv)
{
	t_lem	l;
	t_room	**rooms;
	char	*line;
	t_way	*ways;
	t_turn	**turns;

	if (argc <= 3)
	{
		init_lemin(&l);
		if (!handle_args(argc, argv, &l))
			return (display_usage_message());
		rooms = NULL;
		line = NULL;
		if (!identify_ants_number(&l) || !(identify_rooms(&l, &rooms, &line)))
			return (display_error_message(&l));
		init_dict(&l, rooms);
		if (!get_links(&l, &line))
			return (display_error_message(&l));
		set_levels(&l, &rooms);
		set_linkages(&l, &rooms);
		pave_the_ways(&ways, &l, &rooms);
		define_ways_capacity(&ways, &l);
		print_handled_data(&l, &rooms, &ways);
		move_ants(&l, &ways, &turns);
		sort_result(&turns);
		display_result(&turns);
		return (0);
	}
	// ls: invalid option -- 'z'
	// Try 'ls --help' for more information.
	// bash: cd: -w: invalid option
	// cd: usage: cd [-L|[-P [-e]] [-@]] [dir]


	// printf("%d\n", rooms[0]->level);
	// printf("%d\n", rooms[3]->level);
	// printf("%d\n", rooms[5]->level);
	// printf("%d\n", rooms[6]->level);
//	drop_dead_rooms(&lem, &rooms);

	// while (rooms[i])
	// {
	// 	printf("%s\t", (rooms[i])->name);
	// 	printf("%d\n", (rooms[i])->property);
	// 	i++;
	// }
//	line is on first relation between rooms
//	free_memory(&f);
	return (display_error_message(&l));
}
