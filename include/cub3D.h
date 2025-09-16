/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 13:43:23 by mzimeris          #+#    #+#             */
/*   Updated: 2025/09/16 12:24:30 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "libft.h"
# include <X11/keysym.h>
# include <X11/X.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>

# define WIN_WIDTH 800
# define WIN_HEIGHT 600

typedef struct s_id
{
	char			*key;
	char			*value;
	struct s_id		*next;
}				t_id;

typedef struct s_mandatory_ids
{
	bool	north_texture;
	bool	south_texture;
	bool	west_texture;
	bool	east_texture;
	bool	floor_color;
	bool	ceiling_color;
}				t_mandatory_ids;

typedef struct s_keys
{
	bool	forward;
	bool	backward;
	bool	left;
	bool	right;
	bool	run;
	bool	open;
	bool	fire;
	bool	strafe;
}				t_keys;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}				t_color;

typedef struct s_textures
{
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	t_color	*floor_color;
	t_color	*ceiling_color;
}				t_textures;

typedef struct s_player
{
	char		direction;
	char		position[2];
}				t_player;

typedef struct s_map
{
	char		**grid;
	int			height;
	int			width;
}				t_map;

typedef struct s_data
{
	t_id		*ids;
	t_keys		keys;
	void		*mlx;
	void		*win;
	t_textures	*textures;
	int			width;
	int			height;
	t_map		*map;
	t_player	*player;
	t_lalloc	*allocator;
}				t_data;

int		init_data(t_data **data, t_lalloc *allocator);

int		check_input(t_data *data, char *filename);

int		load_file(char *filename, t_data *data);
int		parse_file(char *filename, t_data **data);
int		is_map_line(char *line);
int		find_map_start(t_data *data);
int		count_map_dimensions(t_data *data, char *line, int fd);
int		parse_map_from_file(t_data **data, char *filename);
int		mandatory_ids_present(t_id *ids);


int		map_check(t_map *map);


int		init_player(t_data *data);

void	clean_data(t_data *data);

void	debug_print_map(t_map *map);
void	debug_print_textures(t_textures *textures);
void	debug_print_player(t_player *player);
void	debug_print_data(t_data *data);


#endif