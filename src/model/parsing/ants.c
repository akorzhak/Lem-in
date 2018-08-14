/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 17:24:05 by akorzhak          #+#    #+#             */
/*   Updated: 2018/07/02 17:24:07 by akorzhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		get_ants(t_lem *l)
{
	char *line;

	line = NULL;
	while (get_next_line(0, &line) > 0)
	{
		save_map_line(l, line);
		if (*line == '#')
		{
			if (ft_strstr(line, "##start") || ft_strstr(line, "##end"))
				return (delete_line_and_exit(&line));
			continue ;
		}
		else if (ft_isdigit(*line))
		{
			if ((l->ants_nb = ft_atoi(line)) <= 0)
				return (delete_line_and_exit(&line));
		}
		else
			return (delete_line_and_exit(&line));
		ft_strdel(&line);
		return (OK);
	}
	return (delete_line_and_exit(&line));
}