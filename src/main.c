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

int 	handle_args(int argc, char **argv, t_lemin *l)
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
	t_lemin	l;
	t_room	**rooms;
	t_room 	**r;
	t_linkage *linked_rooms;
	char	*line;
	t_link	*links;
	t_ways	*ways;
	t_ways 	*w;
	int 	i = 0;
	int n = 0;

	if (argc <= 3)
	{
		init_lemin(&l);
		if (!handle_args(argc, argv, &l))
			return (display_usage_message());
		rooms = NULL;
		line = NULL;
		if (!identify_ants_number(&l) || !(identify_rooms(&l, &rooms, &line)))
			return (display_error_message());
		if (!get_links(&l, &line, &rooms))
			return (display_error_message());
		set_levels(&l, &rooms);
		//	drop_bad_links(&l, &rooms);
		links = l.links;

		printf("\n\t%s\n\n", "PURE LINKS:"); //@DELETE
		while (links) //@DELETE
		{
			printf("%s-%s\n", links->room1, links->room2);
			links = links->next;
		}
		set_linkages(&l, &rooms);

		printf("\n\t%s\n\n", "ADJACENCY LIST:");
		r = rooms;
		while (r[i])
		{
			linked_rooms = r[i]->linked_rooms;
			printf("%s", r[i]->name);
			while (linked_rooms)
			{
				printf("->%s", linked_rooms->room->name);
				linked_rooms = linked_rooms->next;
			}
			printf("\n");
			i++;
		}
		pave_the_ways(&ways, &l, &rooms);
		w = ways;
		printf("\n\t%s\n", "VALID WAYS:");
		while (w)
		{
			n = 0;
			printf("\n");
			printf("%s", w->rooms[n++]->name);
			while (w->rooms[n])
				printf("->%s", w->rooms[n++]->name);
			w = w->next;
		}
		printf("\n");
		define_ways_capacity(&ways, &l);
		w = ways;
		n = 0;
		printf("\n");
		printf("\t%s\n", "WAYS CAPACITIES NB'S:");
		while (w)
		{
			printf("%d way: ", ++n);
				printf("%d\n", w->capacity_nb);
			w = w->next;
		}
		move_ants(&l, &ways);
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
	return (display_error_message());
}
