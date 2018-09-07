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

void		display_error_message(t_lem *l)
{
	t_map	*map;

	map = l->map;
	if (!l->e)
		ft_putstr("ERROR\n");
	else
	{
		red();
		blink();
		ft_putstr("ERROR\n");
		reset();
		if (!l->clone_rooms && map)
		{
			while (map->next)
				map = map->next;
			ft_printf("line %d: %s\n", map->nb, map->line);
		}
		if (l->e_message)
		{
			ft_printf("%s\n", l->e_message);
		}
	}
}

void		display_usage_message(void)
{
	ft_putstr(USAGE);
}
