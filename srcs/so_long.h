/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:19:52 by hlibine           #+#    #+#             */
/*   Updated: 2024/03/20 13:24:35 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <math.h>
# include "../libs/extended_ft/srcs/extended_ft.h"
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

// Compatibilty stuff

# ifdef __APPLE__
#  include "../libs/minilibx_opengl/mlx.h"
# endif

# ifndef __APPLE__
#  include "../libs/minilibx-linux/mlx.h"
# endif

// Animation stuff

# define PLAYER_FRAMES 7.0
# define POINT_FRAMES 27.0

// Rendering stuff

# define SCALE 50

// Img Directories

# define MAP_TEXTURES "map_textures/"
# define POINT_TEXTURES "map_textures/point/point_"
# define SPRITES "player_sprites/player_"
# define ENEMY_TEXTURES "enemy_textures/enemy_"

// Directions

# define LEFT 0
# define DOWN 1
# define RIGHT 2
# define UP 3

// X11 events

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

// Structs

typedef struct s_pos
{
	int	x;
	int	y;
}		t_pos;

typedef struct s_xpm
{
	void	*img;
	int		width;
	int		hight;
}			t_xmp;

typedef struct s_enemy
{
	t_pos	pos;
	t_pos	start_pos;
	int		dir;
	int		waiting;
	double	last_frame_time;
}			t_enemy;

typedef struct s_enemyll
{
	t_enemy				*content;
	struct s_enemyll	*next;
}						t_enemyll;

typedef struct s_point
{
	t_pos	pos;
	int		collected;
}			t_point;

typedef struct s_pointll
{
	t_point				*content;
	struct s_pointll	*next;
}						t_pointll;

typedef struct s_sl
{
	t_xmp		*content;
	struct s_sl	*next;
}	t_sl;

typedef struct s_player
{
	t_pos	pos;
	int		moves;
	int		score;
	int		direction;
	t_sl	*sprites;
	void	*frame;
}			t_player;

typedef struct s_map
{
	char		**data;
	int			score_needed;
	int			length;
	int			width;
	t_pos		spawn;
	t_pos		exit;
	t_xmp		wall;
	t_xmp		floor;
	t_xmp		end;
	t_pointll	*points;
	t_sl		*point_frames;
	t_enemyll	*enemies;
	t_sl		*enemy_texture;
}			t_map;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_mlx
{
	void		*mlx;
	void		*mlx_win;
	t_map		*map;
	char		*map_name;
	t_player	*player;
}			t_mlx;

// Custom functions

t_mlx		*sl_mlx_init(const char *av);
void		sl_error(char *msg);
int			expose_render(t_mlx *game);
void		render_game(t_mlx *game);
t_map		*map_init(const char *av);
void		check_path(t_map *map);
void		sl_movedir(t_mlx *game, char **data, t_player *player, int dir);
void		sl_ent_interact(t_mlx *game);
char		**mapdup(char **data);
void		set_textures(t_mlx *game, t_map *map);
void		set_sprites(t_mlx *game);
t_sl		*sl_lstnew(t_xmp *content);
t_sl		*sl_lstlast(t_sl *lst);
void		sl_lstadd_back(t_sl **lst, t_sl *new);
void		animate(t_mlx *game, double current_time);
void		put_player(t_mlx *game, t_player *player);
void		put_image(t_mlx *game, void *img, int x, int y);
t_pointll	*sl_lstnewpoint(t_point *content);
void		sl_lstadd_front(t_pointll **lst, t_pointll *new);
void		put_points(t_mlx *game);
void		put_moves(t_mlx *game);
void		object_parser(t_map *map);
int			event(t_mlx *game);
t_enemyll	*sl_lstnewenemy(t_enemy *content);
void		sl_addenemy_front(t_enemyll **lst, t_enemyll *new);
void		move_enemy(t_mlx *game, char **data, t_enemy *enemy, int dir);
void		enem_interact(t_mlx *game, int x, int y);
void		restart(t_mlx *game);
void		render_enemy(t_mlx *game, t_enemy *enemy);
int			enem_behave(t_mlx *game, int x, int y);
void		put_enemies(t_mlx *game);

#endif
