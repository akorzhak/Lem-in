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

char	**rooms_dict;

void	init_dict(t_lem *l, t_room **rooms)
{
	int i;

	i = 0;
	rooms_dict = (char **)ft_memalloc(sizeof(char *) * (l->rooms_nb + 1));
	while (i < l->rooms_nb)
	{
		rooms_dict[i] = ft_strdup((rooms[i])->name);
		i++;
	}
}

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

int		dict(t_lem *l, char *value)
{
	int i;

	i = 0;
	while (i < l->rooms_nb)
	{
		if (!ft_strcmp(rooms_dict[i], value))
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
