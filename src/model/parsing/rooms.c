/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
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
		return (ERROR); 
	new->name = ft_strdup(name);
	new->property = property;
	new->next = NULL;
	if (*names == NULL)
	{
		*names = new;
		return (OK);
	}
	while (temp && temp->next)
		temp = temp->next;
	temp->next = new;
	return (OK);
}

int 	record_room_name(char *line, t_namelist **names, int property, t_lem *l)
{
	char **arr;

	if (!*line)
	{
		l->e_message = ft_strdup(EMPTY_LINE);
		return (ERROR);
	}
	arr = ft_split_white(line);
	if (arrlen(arr) != 3)
	{
		l->e_message = ft_strdup(INCOMPLETE_ROOM_DATA);
		return (ERROR);
	}
	if (add_name_to_list(names, arr[0], property) == ERROR)
	{
		free_2darray(&arr);
		return (ERROR);
	}
	if (property == ENTRANCE)
		l->start_room = ft_strdup(arr[0]);
	else if (property == EXIT)
		l->end_room = ft_strdup(arr[0]);
	free_2darray(&arr);
	return (OK);
}


int		form_adjacency_list(t_lem *l, t_room ***rooms, t_namelist *names)
{
	int i;
	t_namelist *head;
	t_room **r;

	i = 0;
	head = names;
	if (!(r = (t_room **)ft_memalloc(sizeof(t_room *) * (l->rooms_nb + 1))))
		return (ERROR);
	while (i < l->rooms_nb)
	{
		if (!(r[i] = (t_room *)ft_memalloc(sizeof(t_room))))
			return (ERROR);
		if (!((r[i])->name = ft_strdup(names->name)))
			return (ERROR);
		(r[i])->property = names->property;
		names = names->next;
		i++;
	}
	r[i] = NULL;
	*rooms = r;
	free_namelist(&head);
	return (OK);
}

int 	handle_commands(char *line, int *property)
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

int 	get_rooms(t_lem *l, t_room ***rooms, char **line)
{
	int property;
	t_namelist *names;

	property = ORDINARY;
	names = NULL;
	while (get_next_line(0, line) > 0 && !ft_strchr(*line, '-'))
	{
		save_map_line(l, *line);
		if (**line == '#')
		{
			if (handle_commands(*line, &property) == ERROR)
				return (delete_line_and_exit(line));
			continue ;
		}
		if (record_room_name(*line, &names, property, l) == ERROR) //1 23 3, null, 1
			return (delete_line_and_exit(line));
		ft_strdel(line);
		property = ORDINARY;
		l->rooms_nb++;
	}
	if (!l->start_room || !l->end_room)
	{
		l->e_message = ft_strdup(NO_START_END_ROOM);
		return (delete_line_and_exit(line));
	}
	if (form_adjacency_list(l, rooms, names) == ERROR)
		return (delete_line_and_exit(line));
	return (OK);
}
