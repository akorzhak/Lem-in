/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   record_name.c                                      :+:      :+:    :+:   */
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
	while (temp)
	{
		if (ft_strcmp(temp->name, name) == EQUAL)
			return (ERROR);
		temp = temp->next;
	}
	temp = *names;
	if (!(new = (t_namelist *)ft_memalloc(sizeof(t_namelist))))
		return (MALLOC_ERROR);
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

int		handle_arr_content(t_lem *l, char **line, char ***arr)
{
	char **array;

	array = *arr;
	if (arrlen(array) < 3)
		return (exit_with_error(l, line, INCOMPLETE_ROOM_DATA));
	if (has_chr(array[1], '\t') || has_chr(array[2], '\t'))
		return (exit_with_error(l, line, TRASH_DELIM));
	if (!is_number(array[1]) || !is_number(array[2]))
		return (exit_with_error(l, line, INVALID_COORDINATE));
	return (OK);
}

int		handle_property(t_lem *l, char **line, int property, char *room_name)
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

int		record_name(char **line, t_namelist **n, int p, t_lem *l)
{
	char	**arr;
	int		res;

	if (!**line)
		return (exit_with_error(l, line, EMPTY_LINE));
	if (count_chr(*line, ' ') != 2)
		return (exit_with_error(l, line, INVALID_FORMAT_ROOM));
	arr = ft_strsplit(*line, ' ');
	if (handle_arr_content(l, line, &arr) == ERROR
		|| handle_property(l, line, p, arr[0]) == ERROR)
	{
		free_2darray(&arr);
		return (ERROR);
	}
	if ((res = add_name_to_list(n, arr[0], p)) != OK)
	{
		free_2darray(&arr);
		if (res == ERROR)
			return (exit_with_error(l, line, CLONE_ROOMS));
		if (res == MALLOC_ERROR)
			return (exit_with_error(l, line, MALLOC_FAIL));
	}
	ft_strdel(line);
	free_2darray(&arr);
	return (OK);
}
