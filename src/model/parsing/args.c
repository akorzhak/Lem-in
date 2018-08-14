/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 17:24:05 by akorzhak          #+#    #+#             */
/*   Updated: 2018/07/02 17:24:07 by akorzhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		handle_args(int argc, char **argv, t_lem *l)
{
	if (argc >= 2)
	{
		if (!ft_strcmp(argv[1], "-e"))
			l->e = 1;
		else if (!ft_strcmp(argv[1], "-a"))
			l->a = 1;
		else
			return (ERROR);
		if (argc == 3)
		{
			if (!ft_strcmp(argv[2], "-e") && !l->e)
				l->e = 1;
			else if (!ft_strcmp(argv[2], "-a") && !l->a)
				l->a = 1;
			else
				return (ERROR);
		}
	}
	return (OK);
}
