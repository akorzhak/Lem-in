/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_turns.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 17:24:05 by akorzhak          #+#    #+#             */
/*   Updated: 2018/07/02 17:24:07 by akorzhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	free_turns(t_turn ***turns)
{
	t_turn	**t;
	t_turn	*next;
	int		i;

	t = *turns;
	i = 0;
	while (t[i])
	{
		while (t[i])
		{
			ft_strdel(&(t[i]->room));
			next = t[i]->next;
			ft_memdel((void **)&t[i]);
			t[i] = next;
		}
		t = *turns;
		i++;
	}
	ft_memdel((void **)&t);
}
