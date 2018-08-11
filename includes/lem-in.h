/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 14:16:49 by akorzhak          #+#    #+#             */
/*   Updated: 2018/06/25 05:51:13 by akorzhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libftprintf.h"
# include <fcntl.h>
# include <stdio.h>

# define ENTRANCE 1
# define EXIT 2
# define ORDINARY 0
# define NOT_USED 0
# define USED 1

typedef struct s_lemin		t_lemin;
typedef struct s_room		t_room;
typedef struct s_link 		t_link;
typedef struct s_linkage	t_linkage;
typedef struct s_ways		t_ways;
typedef struct s_namelist	t_namelist;
typedef struct s_path		t_path;
typedef struct s_ant_room	t_ant_room;

struct 				s_linkage //for adjacency list
{
	t_room			*room;
	t_linkage		*next;
};

struct				s_room
{
	char			*name;
	int				ant; //0 - if empty, 1 - ant nb 1, 2 - ant nb 2...DROP
	int				level; //1, 2, 0 - if invalid path DROP
	int				property; //DROP ???
	char			used;
	t_linkage		*linked_rooms;
};

struct				s_ant_room
{
	char			*name;
	int				ant;
};

struct				s_ways //list of all ways
{
	int				capacity_nb;
	int 			len;
	t_ant_room		**rooms;
	t_ways			*next;
};

struct				s_link 
{
	char			*room1;
	char			*room2;
	t_link 			*next;
};

struct				s_lemin
{
	int				ants_nb;
	int				rooms_nb;
	int				links_nb;
	int 			ways_nb;
	int 			turns;
	char			*start_room;
	char			*end_room;
	t_link			*links;
};

struct				s_namelist
{
	char			*name;
	int				property;
	t_namelist		*next;
};



// struct				s_path
// {
// 	int				capacity;
// 	t_ant_room		*room;
// 	t_path			*next;
// };

void				init_lemin(t_lemin *l);
int					identify_ants_number(t_lemin *l);
int					identify_rooms(t_lemin *l, t_room ***rooms, char **line);
void				delete_2darray(char **arr);
int					delete_line_and_exit(char **line);
void				free_namelist(t_namelist **list);
int					display_error_message(void);
int					get_links(t_lemin *l, char **line, t_room ***rooms);
int					arrlen(char **arr);
void				set_levels(t_lemin *l, t_room ***rooms);
int					dict(t_room **rooms, t_lemin *l, char *value);
void				drop_bad_links(t_lemin *l, t_room ***rooms);
void				set_linkages(t_lemin *l, t_room ***rooms);
void				pave_the_ways(t_ways **ways, t_lemin *l, t_room ***rooms);
void				allocate_ants_by_ways(t_ways **ways, t_lemin *l);
void				move_ants(t_lemin *l, t_ways **ways);

#endif
