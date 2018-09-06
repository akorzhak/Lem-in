/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 17:14:31 by akorzhak          #+#    #+#             */
/*   Updated: 2018/07/02 17:14:34 by akorzhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	free_namelist(t_namelist **list)
{
	t_namelist *next;

	if (list && *list)
	{
		while (*list)
		{
			next = (*list)->next;
			ft_strdel(&(*list)->name);
			ft_memdel((void **)list);
			(*list) = next;
		}
	}
}

void	free_2darray(char ***arr)
{
	int		i;
	char	**array;

	i = 0;
	array = *arr;
	while (array[i])
	{
		ft_strdel(&array[i]);
		i++;
	}
	ft_memdel((void **)arr);
}

int		exit_with_error(t_lem *l, char **line, char *error_message)
{
	l->e_message = ft_strdup(error_message);
	ft_strdel(line);
	return (ERROR);
}

void	free_all(t_lem *l, t_room ***rooms)
{
	free_dict();
	free_lem(l);
	free_rooms(rooms);
}
