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

int		display_error_message(void)
{
	ft_putstr("ERROR\n");
	return (1);
}

int 	display_usage_message(void)
{
	ft_putstr("lem-in: usage: ./lem-in [-e] [-a] < map\n");
	return (1);
}
