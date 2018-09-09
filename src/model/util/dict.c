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

/*
** Emulation of Dictionary object with key-value params.
*/

char	**g_rooms_dict;

void	init_dict(int rooms_nb, t_room **rooms)
{
	int i;

	i = 0;
	g_rooms_dict = (char **)ft_memalloc(sizeof(char *) * (rooms_nb + 1));
	while (i < rooms_nb)
	{
		g_rooms_dict[i] = ft_strdup((rooms[i])->name);
		i++;
	}
}

void	free_dict(void)
{
	int i;

	i = 0;
	if (g_rooms_dict)
	{
		while (g_rooms_dict[i])
		{
			ft_strdel(&g_rooms_dict[i++]);
		}
		ft_memdel((void **)&g_rooms_dict);
	}
}

int		dict(char *value)
{
	int key;

	key = 0;
	while (g_rooms_dict[key])
	{
		if (!ft_strcmp(g_rooms_dict[key], value))
			return (key);
		key++;
	}
	return (-1);
}
