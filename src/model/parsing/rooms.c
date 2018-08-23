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

int 	handle_arr_content(t_lem *l, char **line, char ***arr)
{
	char **array;

	array = *arr;
	if (arrlen(array) < 3)
		return (exit_with_error(l, line, INCOMPLETE_ROOM_DATA));
	else if (arrlen(array) > 3)
		return (exit_with_error(l, line, TOO_MUCH_DATA));
	if (!is_number(array[1]) || !is_number(array[2]))
		return (exit_with_error(l, line, INVALID_COORDINATE));
	return (OK);
}

int 	handle_property(t_lem *l, char **line, int property, char *room_name)
{
	if (property == ENTRANCE)
	{
		if (l->start_room)
			return (exit_with_error(l, line, MULTIPLE_START_END_ROOM));
		l->start_room = ft_strdup(room_name);
	}
	else if (property == EXIT)
	{
		if (l->end_room)
			return (exit_with_error(l, line, MULTIPLE_START_END_ROOM));
		l->end_room = ft_strdup(room_name);
	}
	return (OK);
}

int 	record_room_name(char **line, t_namelist **names, int property, t_lem *l)
{
	char **arr;

	if (!**line)
		return (exit_with_error(l, line, EMPTY_LINE));
	arr = ft_split_white(*line);
	if (handle_arr_content(l, line, &arr) == ERROR
		|| handle_property(l, line, property, arr[0]) == ERROR)
	{
		free_2darray(&arr);
		return (ERROR);
	}
	if (add_name_to_list(names, arr[0], property) == ERROR)
	{
		free_2darray(&arr);
		return (exit_with_error(l, line, MALLOC_ERROR));
	}
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
				return (exit_with_error(l, line, MULTIPLE_START_END_ROOM));
			continue ;
		}
		if (record_room_name(line, &names, property, l) == ERROR)
			return (ERROR);
		ft_strdel(line);
		property = ORDINARY;
		l->rooms_nb++;
	}
	if (!l->start_room || !l->end_room)
		return (exit_with_error(l, line, NO_START_END_ROOM));
	if (form_adjacency_list(l, rooms, names) == ERROR)
		return (exit_with_error(l, line, MALLOC_ERROR));
	return (OK);
}
