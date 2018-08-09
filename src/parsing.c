/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 17:24:05 by akorzhak          #+#    #+#             */
/*   Updated: 2018/07/02 17:24:07 by akorzhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		add_name_to_list(t_namelist **names, char *name, int property)
{
	t_namelist *temp;
	t_namelist *new;

	temp = *names;
	if (!(new = (t_namelist *)ft_memalloc(sizeof(t_namelist))))
		return (-1); 
	new->name = ft_strdup(name);
	new->property = property;
	new->next = NULL;
	if (*names == NULL)
	{
		*names = new;
		return (0);
	}
	while (temp && temp->next)
		temp = temp->next;
	temp->next = new;
	return (0);
}

int 	record_room_name(char *line, t_namelist **names, int property, t_lemin *l)
{
	char **arr;

	if (*line == ' ' || *line == '\n' || *line == '\t')
		return (-1);
	arr = ft_split_white(line);
	if (arrlen(arr) != 3)
		return (-1);
	if (add_name_to_list(names, arr[0], property) == -1)
	{
		delete_2darray(arr);
		return (-1);
	}
	if (property == ENTRANCE)
		l->start_room = ft_strdup(arr[0]);
	else if (property == EXIT)
		l->end_room = ft_strdup(arr[0]);
	delete_2darray(arr);
	return (0);
}

int 	handle_commands(char *line, int *property)
{
	if (ft_strstr(line, "##start"))
	{
		if (*property)
			return (-1);
		*property = ENTRANCE;
	}
	else if (ft_strstr(line, "##end"))
	{
		if (*property)
			return (-1);
		*property = EXIT;
	}
	return (0);
}

int		form_adjacency_list(t_lemin *l, t_room ***rooms, t_namelist *names)
{
	int i;
	t_namelist *head;
	t_room **r;

	i = 0;
	head = names;
	if (!(r = (t_room **)ft_memalloc(sizeof(t_room *) * (l->rooms_nb + 1))))
		return (-1);
	while (i < l->rooms_nb)
	{
		if (!(r[i] = (t_room *)ft_memalloc(sizeof(t_room))))
			return (-1);
		if (!((r[i])->name = ft_strdup(names->name)))
			return (-1);
		(r[i])->property = names->property;
		names = names->next;
		i++;
	}
	r[i] = NULL;
	*rooms = r;
	free_namelist(&head);
	return (0);
}

int 	identify_rooms(t_lemin *l, t_room ***rooms, char **line)
{
	int property;
	t_namelist *names;

	property = ORDINARY;
	names = NULL;
	while (get_next_line(0, line) > 0 && !ft_strchr(*line, '-'))
	{
		ft_printf("%s\n", *line);
		if (**line == '#')
		{
			if (handle_commands(*line, &property) == -1)
				return (delete_line_and_exit(line));
			continue ;
		}
		if (record_room_name(*line, &names, property, l) == -1) //1 23 3, null, 1
			return (delete_line_and_exit(line));
		ft_strdel(line);
		property = ORDINARY;
		l->rooms_nb++;
	}
	if (form_adjacency_list(l, rooms, names) == -1)
		return (delete_line_and_exit(line));
	return (1);
}

int		identify_ants_number(t_lemin *l)
{
	char *line;

	line = NULL;
	while (get_next_line(0, &line) > 0)
	{
		ft_printf("%s\n", line);
		if (*line == '#')
		{
			if (ft_strstr(line, "##start") || ft_strstr(line, "##end"))
				return (delete_line_and_exit(&line));
			ft_printf("%s\n", *line);
			continue ;
		}
		else if (ft_isdigit(*line))
		{
			if ((l->ants_nb = ft_atoi(line)) <= 0)
				return (delete_line_and_exit(&line));
		}
		else
			return (delete_line_and_exit(&line));
		ft_strdel(&line);
		return (1);
	}
	return (delete_line_and_exit(&line));
}

void	record_links(t_lemin *l, char *room1, char *room2)
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
	ft_printf("%s-%s\n", room1, room2);
}

int 	get_links(t_lemin *l, char **line, t_room ***rooms)
{
	char **arr;
	int 	i_room1;
	int 	i_room2;
	t_room 	**r;

	r = *rooms;
	do
	{
		if (**line == '#')
		{
			if (ft_strstr(*line, "##start") || ft_strstr(*line, "##end"))
				return (delete_line_and_exit(line));
			ft_printf("%s\n", *line);
			continue ;
		}
		arr = ft_strsplit(*line, '-');
		i_room1 = dict(r, l, arr[0]);
		i_room2 = dict(r, l, arr[1]);
		if (arrlen(arr) != 2 || !ft_strcmp(arr[0], arr[1])
			|| i_room1 == -1 || i_room2 == -1)
		{
			delete_2darray(arr);
			return (0);
		}
		record_links(l, arr[0], arr[1]);
		delete_2darray(arr);
		ft_strdel(line);
	} while (get_next_line(0, line) > 0);
	return (1);
}

void	set_1st_levels(t_lemin *l, t_room ***rooms)
{
	t_room **r;
	t_link *links;
	int 	level;

	r = *rooms;
	level = 1;
	links = l->links;
	while (links)
	{
		while (links && ft_strcmp(links->room1, l->start_room)
			&& ft_strcmp(links->room2, l->start_room))
			links = links->next;
		if (!links)
			return ;
		if (!ft_strcmp(links->room1, l->start_room))
		{
			r[dict(r, l, links->room1)]->level = level;
			r[dict(r, l, links->room2)]->level = level + 1;
		}
		else if (!ft_strcmp(links->room2, l->start_room))
		{
			r[dict(r, l, links->room2)]->level = level;
			r[dict(r, l, links->room1)]->level = level + 1;
		}
		links = links->next;
	}
}

void	free_the_link(t_link **links)
{
	ft_strdel(&(*links)->room1);
	ft_strdel(&(*links)->room2);
	ft_memdel((void **)links);
}

void	drop_the_link(t_lemin *l, t_link **links)
{
	t_link *temp;

	temp = l->links;
	if (temp == (*links))
	{
		temp = temp->next;
		free_the_link(links);
		(*links) = temp;
	}
	else
	{
		while (temp->next && temp->next != (*links))
			temp = temp->next;
		if ((*links)->next == NULL)
		{
			temp->next = NULL;
			free_the_link(links);
		}
		else
		{
			temp->next = temp->next->next;
			free_the_link(links);
			(*links) = temp->next;
		}
	}
}

void	drop_bad_links(t_lemin *l, t_room ***rooms)
{
	int 	lvl_room1;
	int 	lvl_room2;
	t_link 	*links;
	t_room 	**r;
	
	links = l->links;
	r = *rooms;
	while (links)
	{
		lvl_room1 = r[dict(r, l, links->room1)]->level;
		lvl_room2 = r[dict(r, l, links->room2)]->level;
		if (lvl_room1 == lvl_room2 && ft_strcmp(links->room1, l->end_room)
			&& ft_strcmp(links->room2, l->end_room))
		{
			drop_the_link(l, &links);
		}
		else
			links = links->next;
	}
}

void	set_levels(t_lemin *l, t_room ***rooms)
{
	t_room **r;
	t_link *links;
	int 	level;
	char 	change;

	r = *rooms;
	int i = 0; //@TEST ONLY !!!!!!!!!!!!!!!!!!!!!!!!!
//	r[dict(r, l, l->end_room)]->level = -1;
	set_1st_levels(l, rooms);
	do
	{
		change = 0;
		links = l->links;
		while (links)
		{
			if (ft_strcmp(links->room1, l->end_room)
				&& (level = r[dict(r, l, links->room1)]->level)
				&& !r[dict(r, l, links->room2)]->level)
			{
				r[dict(r, l, links->room2)]->level = level + 1;
				change = 1;
			}
			else if (ft_strcmp(links->room2, l->end_room)
				&& (level = r[dict(r, l, links->room2)]->level)
				&& !r[dict(r, l, links->room1)]->level)
			{
				r[dict(r, l, links->room1)]->level = level + 1;
				change = 1;
			}
			links = links->next;
		}
	} while (change);
	printf("\n\t%s\n\n", "BREADTH FIRST SEARCH:");
	while (r[i]) //@TEST ONLY !!!!!!!!!!!!!!!!!!!!!!
	{
		printf("name: %s\t", r[i]->name);
		printf("level: %d\n", r[i]->level);
		i++;
	}
}

void	link_the_rooms(t_lemin *l, t_room ***rooms, int i, char *linked_room)
{
	t_room **r;
	t_linkage *linked_rooms;

	r = *rooms;
	linked_rooms = r[i]->linked_rooms;
	if (!linked_rooms)
	{
		linked_rooms = (t_linkage *)malloc(sizeof(t_linkage));
		r[i]->linked_rooms = linked_rooms;
	}
	else
	{
		while (linked_rooms->next)
			linked_rooms = linked_rooms->next;
		linked_rooms->next = (t_linkage *)malloc(sizeof(t_linkage));
		linked_rooms = linked_rooms->next;
	}
	linked_rooms->room = r[dict(r, l, linked_room)];
}

void	set_linkages(t_lemin *l, t_room ***rooms)
{
	int 	i;
	t_room **r;
	t_link *links;

	i = 0;
	r = *rooms;
	while(r[i])
	{
		links = l->links;
		while (links)
		{
			while (links && ft_strcmp(r[i]->name, links->room1)
						&& ft_strcmp(r[i]->name, links->room2))
				links = links->next;
			if (!links)
				break ;
			if (!ft_strcmp(r[i]->name, links->room1))
				link_the_rooms(l, rooms, i, links->room2);
			else if (!ft_strcmp(r[i]->name, links->room2))
				link_the_rooms(l, rooms, i, links->room1);
			links = links->next;
		}
		i++;
	}
}

t_linkage *choose_penultimate_room(t_linkage **linked_rooms)
{
	int 	lowest_lvl = 0;
	t_linkage 	*rooms;
	t_linkage 	*penultimate_room;

	rooms = *linked_rooms;
	penultimate_room = NULL;
	while (rooms)
	{
		if ((!lowest_lvl || rooms->room->level < lowest_lvl)
			&& (rooms->room->used == NOT_USED) && rooms->room->level)
		{
			lowest_lvl = rooms->room->level;
			penultimate_room = rooms;
		}
		rooms = rooms->next;
	}
	return (penultimate_room);
}

void	drop_the_way(char ***way, int i)
{
	char **w;

	w = *way;
	while (w[i])
		ft_strdel(&w[i--]);
	// free(way);
	// way = NULL;
	ft_memdel((void **)*way);
}

void	pave_the_ways(t_ways **ways, t_lemin *l, t_room ***rooms)
{
	int 	i;
	int 	len;
	int 	last_room_index;
	t_room **r;
	t_linkage *penultimate_room;
	t_linkage *link;
//	t_linkage *head;
	char	**way;
	t_ways 	*w;
	int fl;

	i = 0;
	r = *rooms;
	*ways = (t_ways *)ft_memalloc(sizeof(t_ways));
	w = *ways;
	fl = 0;
	while (ft_strcmp(r[i]->name, l->end_room))
		i++;
	r[i]->used = USED;
	while ((penultimate_room = choose_penultimate_room(&(r[i]->linked_rooms))))
	{
		len = penultimate_room->room->level + 2;
		way = (char **)ft_memalloc(sizeof(char *) * len--); //for end room & null;
		way[--len] = ft_strdup(l->end_room);
		last_room_index = len;
		way[--len] = ft_strdup(penultimate_room->room->name);
		penultimate_room->room->used = USED;
		link = penultimate_room->room->linked_rooms;
//		head = link; //kick
		while (len)
		{
			while (link && (link->room->level != (len + fl) || (link->room->used
				&& ft_strcmp(link->room->name, l->start_room))))
				link = link->next;
			// if (!link && !fl) //maybe kick
			// {
			// 	link = head;
			// 	fl = 1;
			// 	continue ;
			// }
			// else if (!link && fl) //kick
			// 	break ;
			if (!link)
				break ;
			way[--len] = ft_strdup(link->room->name);
			link->room->used = USED;
			link = link->room->linked_rooms;
		//	head = link;
		}
		if (!way[0])
		{
			drop_the_way(&way, last_room_index);
			break ;
		}
		if (w->way)
		{
			w->next = (t_ways *)ft_memalloc(sizeof(t_ways));
			w = w->next;
		}
		w->way = (t_way *)ft_memalloc(sizeof(t_way));
		w->way->rooms = way;
		l->ways_nb++;
	}
}

void	define_nb_of_transfers(t_ways **ways)
{
	int len;
	t_ways 	*w;

	len = 0;
	w = *ways;
	while (w)
	{
		while (w->way->rooms[len])
			len++;
		w->way->len = --len;
		w = w->next;
	}
}

int 	calculate_total_ways_len(t_ways *ways)
{
	int 	total_len;

	total_len = 0;
	while (ways)
	{
		total_len += ways->way->len;
		ways = ways->next;
	}
	return (total_len);
}

void	define_capacity_pc_for_2_ways(t_ways **w)
{
	int 	total_len;
	float 	pc_unit;

	total_len = calculate_total_ways_len(*w);
	pc_unit = 100.0 / total_len;
	(*w)->way->capacity_pc = (*w)->next->way->len * pc_unit / 100.0;
	(*w)->next->way->capacity_pc = 1 - (*w)->way->capacity_pc;
}

void	define_capacity_pc_for_n_ways(t_ways **ways, int ways_nb)
{
	int 	way1_len;	
	float	sum_pc;
	float 	pc_unit;
	float	difference;
	t_ways *w;
	char flag = 2;

	w = *ways;
	way1_len = w->way->len;
	pc_unit = 100.0 / ways_nb;
	while (flag--) 
	{
		sum_pc = 0;
		w = *ways;
		while (w)
		{
			w->way->capacity_pc = (pc_unit * way1_len) / w->way->len / 100.0;
			sum_pc += w->way->capacity_pc;
			w = w->next;
		}
		difference = 1.0 - sum_pc;
	//	printf("sum_pc: %f\n", sum_pc);
	//	printf("difference: %f\n", difference);
		if (difference > 0.01)
		{
			pc_unit += pc_unit * (difference / sum_pc);
	//		printf("PC_UNIT: %f\n", pc_unit);
		}
		else
			break ;
	}
}

void	define_capacity_in_percents(t_ways **w, int ways_nb)
{
	if (ways_nb == 1)
		(*w)->way->capacity_pc = 1;
	else if (ways_nb == 2)
		define_capacity_pc_for_2_ways(w);
	else
		define_capacity_pc_for_n_ways(w, ways_nb); //other algo

}

void	define_capacity_nb_for_2_ways(t_ways **w, int ants_nb)
{
	(*w)->next->way->capacity_nb = ants_nb * (*w)->next->way->capacity_pc;
	(*w)->way->capacity_nb = ants_nb - (*w)->next->way->capacity_nb;
}

void	define_capacity_nb_for_n_ways(t_ways **ways, int ants_nb)
{
	t_ways *w;
	int 	ants_allocated;

	ants_allocated = 0;
	w = (*ways)->next;
	while (w)
	{
		w->way->capacity_nb = ants_nb * w->way->capacity_pc;
		ants_allocated += w->way->capacity_nb;
		w = w->next;
	}
	w = *ways;
	w->way->capacity_nb = ants_nb - ants_allocated;
}

void	define_capacity_in_numbers(t_ways **w, int ways_nb, int ants_nb)
{
	if (ways_nb == 1)
		(*w)->way->capacity_nb = ants_nb;
	else if (ways_nb == 2)
		define_capacity_nb_for_2_ways(w, ants_nb);
	else
		define_capacity_nb_for_n_ways(w, ants_nb);
}

void	allocate_ants_by_ways(t_ways **ways, t_lemin *l)
{
	define_nb_of_transfers(ways);
	define_capacity_in_percents(ways, l->ways_nb);
	define_capacity_in_numbers(ways, l->ways_nb, l->ants_nb);
}
