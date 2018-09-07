/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 17:40:07 by akorzhak          #+#    #+#             */
/*   Updated: 2018/07/02 17:40:10 by akorzhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		has_spaces(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			return (1);
		i++;
	}
	return (0);
}

int		is_number(char *nb)
{
	int	i;

	i = 0;
	if (nb[i] == '-' || nb[i] == '+')
		i++;
	while (ft_isdigit(nb[i]))
	{
		i++;
		if (!nb[i])
			return (1);
	}
	return (0);
}

int		ft_ceil(int nb1, int nb2)
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

int		arrlen(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}
