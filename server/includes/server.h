/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** .h for server
*/

#ifndef SERVER_H_
# define SERVER_H_

# include <sys/select.h>

typedef enum item_type{
	LINEMATE,
	DERAUMERE,
	SIBUR,
	MENDIANE,
	PHIRAS,
	THYSTAME,
	FOOD
}item_type;

typedef enum direction{
	NORTH,
	EAST,
	SOUTH,
	WEST
}direction;

typedef	struct s_pos
{
	int x;
	int y;
}t_pos;

typedef	struct s_map
{
	t_pos pos;
	int objects[7];
}t_map;

typedef struct s_team
{
	char *team_name;
	int team_max;
	int team_count;
}t_team;

typedef struct s_cmd
{
	char name[100];
	int time;
	void (*ptr)();
}t_cmd;

typedef struct s_stacknode
{
	t_cmd *cmd;
	char *args;
	struct s_stacknode *next;
}t_stacknode;

typedef struct s_stack
{
	int count;
	struct timeval time;
	t_stacknode *top;
}t_stack;

typedef	struct s_player
{
	int sock;
	t_stack cmd_stack;
	char *team_name;
	t_pos pos;
	int inv[7];
	int level;
	direction dir;
	int elevation;
	int ears;
	struct s_player	*next;
}t_player;

typedef	struct s_eggs
{
	t_pos pos;
	char *team_name;
	struct timeval time;
	struct s_eggs *next;
}t_eggs;

typedef	struct s_server
{
	fd_set master;
	int width;
	int height;
	t_map **planete;
	t_player *players;
	t_team **team;
	t_eggs *eggs;
	int team_max;
	int freq;
	int port;
}t_server;

typedef struct s_params
{
	char *cmd;
	void (*cmd_func)(char **, int, t_server *);
}t_params;

typedef struct s_broadcasting
{
	direction dir;
	void (*cmd_func)(t_server *, t_player *, int *, char *);
}t_broadcasting;

typedef struct s_facing
{
	direction dir;
	void (*cmd_func)(int, direction, char *);
}t_facing;

typedef struct s_ressources
{
	char *name;
}t_ressources;

typedef struct s_word
{
	int i;
	char *str;
}t_word;

typedef struct s_looking
{
	direction dir;
	void (*cmd_func)(t_server *, t_player *, int *, t_word *);
}t_looking;

/*	Function declaration	*/

t_map		**create_map(t_server *);
void		show_map(int sock, t_server *);

void		check_params(int, char **, t_server *);
void		check_port(char **, int, t_server *);
void		check_width(char **, int, t_server *);
void		check_height(char **, int, t_server *);
void		check_names(char **, int, t_server *);
void		check_nb(char **, int, t_server *);
void		check_freq(char **, int, t_server *);
void		help(char **, int, t_server *);

t_player	*new_player(int sock);

void		add_player(t_player** head, int sock, t_server *server);
t_player	*search_player(t_player *head, int sock);
void		remove_player(t_player **head, int sock);
int		get_team_count(t_player* head, char *team_name);

int		create_sock(int port);
void		run(t_server *server, int sock);

int		stack_push(t_stack *stack, t_cmd *cmd, char *args);
t_cmd		*stack_top(t_stack *stack);
t_cmd		*stack_pop(t_stack *stack);
int		is_stack_empty(t_stack *stack);
t_stacknode	*alloc_stacknode(t_cmd *cmd);

int		get_ressources(t_map *, int, t_server *, t_word *);

void		check_inventory(int sock, t_server *server);

void		move_player(int sock, t_server *server);
void		turn_left(int sock, t_server *server);
void		turn_right(int sock, t_server *server);

void		connect_nbr(int sock, t_server *server);

t_team		*get_pteam(t_player *player, t_server *server);

void		look(int, t_server *);
void    	look_self(t_server *, t_player *, t_word *);
void		look_north(t_server *, t_player *, int *, t_word *);
void		look_south(t_server *, t_player *, int *, t_word *);
void		look_east(t_server *, t_player *, int *, t_word *);
void		look_west(t_server *, t_player *, int *, t_word *);

void		broadcast(int sock, t_server *server, char *m);
void		broadcast_s(t_server *, t_player *, int *, char *);
void    	broadcast_north(t_server *server,
		t_player *player, int *ac, char *mess);
void    	broadcast_south(t_server *server,
		t_player *player, int *ac, char *mess);
void    	broadcast_east(t_server *server,
		t_player *player, int *ac, char *mess);
void    	broadcast_west(t_server *server,
		t_player *player, int *ac, char *mess);

void    	check_pressence(t_server *server,
		direction dir, t_pos pos, char *mess);
void    	check_origin(t_server *server, t_pos pos, char *mess);
void    	facing_north(int sock, direction dir, char *mess);
void    	facing_south(int sock, direction dir, char *mess);
void    	facing_east(int sock, direction dir, char *mess);
void    	facing_west(int sock, direction dir, char *mess);
void		set_ears(t_server *);

void		take_object(int sock, t_server *server, char *args);
void		drop_object(int sock, t_server *server, char *args);

void		do_elevation(int sock, t_server *server);
int		incantation(char *cmd, int sock, t_server *server);

void		initialize_player_team(int sock, t_server *server);
void		handle_cmd(int sock, t_server *server);

void		check_sock(int i, int sock,
		fd_set *read_set, t_server *server);
void		stack_tick(t_server *server);
void		food_tick(t_server *server);
void		eggs_tick(t_server *server);

void		ejection(int sock, t_server *server);
void		dir_eject_north(t_server *server, t_player *npc);
void		dir_eject_south(t_server *server, t_player *npc);
void		dir_eject_west(t_server *server, t_player *npc);
void		dir_eject_east(t_server *server, t_player *npc);

void		add_word(t_word *, char *);
t_word		*set_word();

void		item_on_case(int sock, t_server *server, char *args);
void		get_players(int sock, t_server *server);
t_map		*get_pcase(t_player *player, t_server *server);

void		fork_player(int sock, t_server *server);
void		egg_on_case(t_map *map, t_server *server, t_word *word);
void		eclosion(t_server *server, t_eggs *egg);

#endif /* SERVER_H_ */
