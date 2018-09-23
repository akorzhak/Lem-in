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

#include "lemin.h"

int		validate_ants_nb(char **line, t_lem *l)
{
	if (**line == '0')
		return (exit_with_error(l, line, INVALID_ANTS_NB));
	if (is_number(*line) == FALSE)
		return (exit_with_error(l, line, ANTS_NOT_NUMBER));
	if (ft_strlen(*line) > 10 || (l->ants_nb = ft_atoi(*line)) > 21000000)
		return (exit_with_error(l, line, TOO_MUCH_ANTS));
	else if (l->ants_nb <= 0)
		return (exit_with_error(l, line, INVALID_ANTS_NB));
	return (OK);
}

int		get_ants(t_lem *l)
{
	char *line;

	line = NULL;
	while (get_next_line(0, &line) == TRUE)
	{
		if (save_map_line(l, line) == MALLOC_ERROR)
			return (exit_with_error(l, &line, MALLOC_FAIL));
		if (*line == '#')
		{
			if (!ft_strcmp(line, "##start") || !ft_strcmp(line, "##end"))
				return (exit_with_error(l, &line, COMMAND_BEFORE_NB));
			ft_strdel(&line);
			continue ;
		}
		else
		{
			if (validate_ants_nb(&line, l) == ERROR)
				return (ERROR);
		}
		ft_strdel(&line);
		return (OK);
	}
	return (exit_with_error(l, &line, EMPTY_MAP));
}
