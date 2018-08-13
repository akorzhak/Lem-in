/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 17:40:07 by akorzhak          #+#    #+#             */
/*   Updated: 2018/07/02 17:40:10 by akorzhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int 	ft_ceil(int nb1, int nb2)
{
	int		res;

	if (nb2)
	{
		res = nb1 / nb2;
		if (nb1 % nb2)
			res++;
		return (res);
	}
	return (0);
}

int		dict(t_room **rooms, t_lem *l, char *value)
{
	int i;
	static char **values;

	values = (char **)ft_memalloc(sizeof(char *) * l->rooms_nb);
	i = 0;
	while (rooms[i])
	{
		values[i] = ft_strdup((rooms[i])->name);
		i++;
	}
	i = 0;
	while (i < l->rooms_nb)
	{
		if (!ft_strcmp(values[i], value))
			return (i);
		i++;
	}
	return (-1);
}

int		arrlen(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	delete_2darray(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
	//	printf("%s\n", arr[i]);
		ft_strdel(&arr[i]);
	//	printf("%s\n", arr[i]);
		i++;
	}
	ft_memdel((void **)arr);
}

int 	delete_line_and_exit(char **line)
{
	ft_strdel(line);
	return (0);
}
