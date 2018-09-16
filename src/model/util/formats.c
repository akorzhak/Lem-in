/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_steps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 17:24:05 by akorzhak          #+#    #+#             */
/*   Updated: 2018/07/02 17:24:07 by akorzhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Escape sequences for formats.
*/

void	blink(void)
{
	ft_putstr("\033[5m");
}

void	underline(void)
{
	ft_putstr("\033[4m");
}

void	reset(void)
{
	ft_putstr("\033[0m");
}
