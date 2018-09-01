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
# define OK 0
# define ERROR 1

/***************************** STRING CONSTANTS *******************************/
# define EMPTY_LINE "Empty line."
# define TO_DO "TO DO!"
# define IRRELEVANT_COMMAND "Irrelevant START/END command."
# define INCOMPLETE_ROOM_DATA "Room name or coordinate is absent."
# define TOO_MUCH_DATA "Redundant data is provided."
# define INCOMPLETE_LINK_DATA "Room name or dash is absent."
# define INVALID_ROOM "Such room is NOT declared: "
# define INVALID_COORDINATE "Coordinate is not a number."
# define NO_START_END_ROOM "Parsing reached the end of the map. "\
							"No START or END room found."
# define SELF_LINKED_ROOM "Room can NOT link itself."
# define NO_LINKS "Parsing reached the end of the map. No LINKS found."
# define MULTIPLE_START_END_ROOM "Multiple declaration of START/END room " \
							"is forbidden."			
# define SPACES "LINKS can NOT contain any spaces or tabs."
# define INVALID_ANTS_NB "Invalid ants number."
# define MALLOC_ERROR "Memory allocation has failed."
# define USAGE "lem-in: usage: ./lem-in [-e] [-a] < map\n"

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
typedef struct s_i			t_i;
typedef struct s_lnk		t_lnk;

struct 				s_map
{
	char			*line;
	int 			nb;
	t_map			*next;
};

struct 				s_linkage
{
	t_room			*room;
	t_linkage		*next;
};

struct				s_room
{
	char			*name;
	int				level;
	int				property;
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

struct 				s_i
{
	int 			i;
	int 			len;
	int 			lenth;
	int 			last_room_index;
};

struct 				s_lnk
{
	t_linkage 		*penultimate_room;
	t_linkage 		*link;
};

/******************************* PARSING FUNCTIONS ***************************/
int					handle_args(int argc, char **argv, t_lem *l);
int					get_ants(t_lem *l);
int					get_rooms(t_lem *l, t_room ***rooms, char **line);
int 				record_name(char **line, t_namelist **n, int p, t_lem *l);
int					form_adj_list(t_lem *l, t_room ***rooms, t_namelist *names);


/******************************* SAVE_MAP FUNCTION ***************************/
void				save_map_line(t_lem *l, char *line);
void				save_link(t_lem *l, char *room1, char *room2);

void				init_lemin(t_lem *l);
int 				display_usage_message(void);
int					exit_with_error(t_lem *l, char **line, char *error_massage);
void				display_error_message(t_lem *l);
int					get_links(t_lem *l, char **line);
void				set_levels(t_lem *l, t_room ***r);
void				set_links(t_lem *l, t_room ***r);
void				pave_the_ways(t_way **ways, t_lem *l, t_room **rooms);
void				set_ways_capacity(t_way **w, t_lem *l);
void				move_ants(t_lem *l, t_way **ways, t_turn ***turns);

/******************************* SORT FUNCTION ********************************/
void				sort_result(t_turn ***turns);

void				print_handled_data(t_lem *l, t_room **rooms, t_way **ways);
void				display_result(t_turn ***turns);

/******************************* FREE FUNCTIONS *******************************/
void				free_all(t_lem *l, t_room ***rooms);
void				free_lem(t_lem *l);
void				free_2darray(char ***arr);
void				free_namelist(t_namelist **list);
void				free_rooms(t_room ***rooms);


/******************************* MATH FUNCTIONS *******************************/
int					arrlen(char **arr);
int					ft_ceil(int nb1, int nb2);
int					is_number(char	*nb);
int					has_spaces(char	*str);

/******************************* DICT FUNCTIONS *******************************/
void				init_dict(t_lem *l, t_room **rooms);
int					dict(t_lem *l, char *value);
void				free_dict(void);

/******************************* VIEW FUNCTIONS *******************************/
void				display_map(t_map *map);
void				display_bfs(t_room **rooms);
void				display_adjacency_list(t_room **rooms);
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
