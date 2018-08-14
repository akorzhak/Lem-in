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

/***************************** STRING CONSTANTS *******************************/
# define INCOMPLETE_ROOM_DATA "room name or coordinate is absent"
# define INCOMPLETE_LINK_DATA "room name or dash is absent"
# define INVALID_ROOM " - no such room"
# define NO_START_END_ROOM "Parsing has reached the end of the map. "\
							"No START or END room found."



extern int line_nb;
extern char **rooms_dict;

typedef struct s_lem		t_lem;
typedef struct s_map		t_map;
typedef struct s_room		t_room;
typedef struct s_link 		t_link;
typedef struct s_linkage	t_linkage;
typedef struct s_way		t_way;
typedef struct s_namelist	t_namelist;
typedef struct s_turn		t_turn;
typedef struct s_ant_room	t_ant_room;
typedef struct s_sort		t_sort;

struct 				s_map
{
	char			*line;
	int 			nb;
	t_map			*next;
};

struct 				s_linkage //for adjacency list
{
	t_room			*room;
	t_linkage		*next;
};

struct				s_room
{
	char			*name;
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

struct				s_way //list of all ways
{
	int				capacity_nb;
	int 			len;
	t_ant_room		**rooms;
	t_way			*next;
};

struct				s_link 
{
	char			*room1;
	char			*room2;
	t_link 			*next;
};

struct				s_lem
{
	char			e;
	char			a;
	int				ants_nb;
	int				rooms_nb;
	int				links_nb;
	int 			ways_nb;
	int 			turns;
	char			*start_room;
	char			*end_room;
	char			*e_message;
	t_map			*map;
	t_link			*links;
};

struct				s_namelist
{
	char			*name;
	int				property;
	t_namelist		*next;
};

struct				s_turn
{
	char			*room;
	int				ant;
	t_turn			*next;
};

struct 				s_sort
{
	t_turn			*prior;
	t_turn			*loop;
	t_turn			*prev;
	t_turn			*sort;
};

void				init_lemin(t_lem *l);
int 				display_usage_message(void);
int					identify_ants_number(t_lem *l);
int					identify_rooms(t_lem *l, t_room ***rooms, char **line);
void				delete_2darray(char **arr);
int					delete_line_and_exit(char **line);
void				free_namelist(t_namelist **list);
int					display_error_message(t_lem *l);
int					get_links(t_lem *l, char **line);
void				set_levels(t_lem *l, t_room ***rooms);
void				set_linkages(t_lem *l, t_room ***rooms);
void				pave_the_ways(t_way **ways, t_lem *l, t_room ***rooms);
void				define_ways_capacity(t_way **w, t_lem *l);
void				move_ants(t_lem *l, t_way **ways, t_turn ***turns);

/******************************* SORT FUNCTION ********************************/
void				sort_result(t_turn ***turns);

void				print_handled_data(t_lem *l, t_room ***rooms, t_way **ways);
void				display_result(t_turn ***turns);

/******************************* UTIL FUNCTIONS *******************************/
void				init_dict(t_lem *l, t_room **rooms);
int					dict(t_lem *l, char *value);
int					arrlen(char **arr);
int					ft_ceil(int nb1, int nb2);

/******************************* VIEW FUNCTIONS *******************************/
void				display_map(t_map *map);
void				display_bfs(t_room ***rooms);
void				display_adjacency_list(t_room ***rooms);
void				display_valid_ways(t_way **ways);
void				display_ways_capacity(t_way **ways);

/******************************* COLORS FUNCTIONS *****************************/
void				red(void);
void				yellow(void);
void				green(void);
void				blue(void);

/******************************* FORMAT FUNCTIONS ******************************/
void				blink(void);
void				underline(void);
void				reset(void);

#endif
