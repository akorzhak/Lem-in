/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict.c                                             :+:      :+:    :+:   */
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
	int 	i;

	i = 0;
	rooms_dict = (char **)ft_memalloc(sizeof(char *) * (l->rooms_nb + 1));
	while (i < l->rooms_nb)
	{
		rooms_dict[i] = ft_strdup((rooms[i])->name);
		i++;
	}
}

void	free_dict(void)
{
	int 	i;

	i = 0;
	if (rooms_dict)
	{
		while(rooms_dict[i])
			ft_strdel(&rooms_dict[i++]);
		ft_memdel((void **)&rooms_dict);
	}
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
