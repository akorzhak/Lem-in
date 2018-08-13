/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 17:31:56 by akorzhak          #+#    #+#             */
/*   Updated: 2018/07/05 17:31:58 by akorzhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		display_error_message(t_lem *l)
{
	t_map	*map;

	map = l->map;
	if (!l->e)
		ft_putstr("ERROR\n");
	else
	{
		blink();
		red();
		ft_putstr("ERROR\n");
		reset();
		while (map && map->next)
			map = map->next;
		ft_printf("line %d: %s\n", map->nb, map->line);
		if (l->e_message)
		{
		//	red();
			ft_putstr(l->e_message);
		//	reset();
		}
		ft_putchar('\n');
	}
	return (1);
}

int 	display_usage_message(void)
{
	ft_putstr("lem-in: usage: ./lem-in [-e] [-a] < map\n");
	return (1);
}
