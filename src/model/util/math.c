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

int		has_chr(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int		count_chr(char *str, char c)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (str[i])
	{
		if (str[i] == c)
			nb++;
		i++;
	}
	return (nb);
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
			return (TRUE);
	}
	return (FALSE);
}

/*
** Function divides two integers,
** rounding result to ceil number.
*/

int		ceil_div(int nb1, int nb2)
{
	int		res;

	if (nb2)
	{
		res = nb1 / nb2;
		if (nb1 % nb2)
			res++;
		return (res);
	}
	return (FALSE);
}

int		arrlen(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}
