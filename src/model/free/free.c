/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 17:14:31 by akorzhak          #+#    #+#             */
/*   Updated: 2018/07/02 17:14:34 by akorzhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	free_namelist(t_namelist **list)
{
	t_namelist *next;

	if (list && *list)
	{
		while (*list)
		{
			next = (*list)->next;
			ft_strdel(&(*list)->name);
			ft_memdel((void **)list);
			(*list) = next;
		}
	}
}

void	free_2darray(char ***arr)
{
	int 	i;
	char	**array;

	i = 0;
	array = *arr;
	while (array[i])
	{
	//	printf("%s\n", arr[i]);
		ft_strdel(&array[i]);
	//	printf("%s\n", arr[i]);
		i++;
	}
	ft_memdel((void **)array);
}

int 	exit_with_error(t_lem *l, char **line, char *error_message)
{
	l->e_message = ft_strdup(error_message);
	ft_strdel(line);
	return (ERROR);
}

void	free_all(t_lem *l, t_room ***rooms)
{
	free_dict();
	free_lem(l);
	free_rooms(rooms);
}
// void	free_the_grid_data(t_grid *grid)
// {
// 	int i;

// 	i = 0;
// 	if (grid->data)
// 	{
// 		while (grid->data[i])
// 		{
// 			ft_strdel(&grid->data[i]);
// 			i++;
// 		}
// 		ft_memdel((void **)&grid->data);
// 	}
// }

// void	free_dist_board(t_filler *f)
// {
// 	int i;

// 	i = 0;
// 	while (i < f->board->rows)
// 	{
// 		ft_memdel((void **)&f->dist_board[i]);
// 		i++;
// 	}
// 	ft_memdel((void **)f->dist_board);
// }

// void	free_memory(t_filler *f)
// {
// 	free_dist_board(f);
// 	free_the_grid_data(f->board);
// 	free_the_grid_data(f->piece);
// 	ft_memdel((void **)&f->board);
// 	ft_memdel((void **)&f->piece);
// }
