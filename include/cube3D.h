/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 13:43:23 by mzimeris          #+#    #+#             */
/*   Updated: 2025/09/15 17:58:28 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

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

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}			t_color;

typedef struct s_textures
{
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	t_color	*floor_color;
	t_color	*ceiling_color;
}			t_textures;

typedef struct s_player
{
	char		direction;
	char		position;
}			t_player;

typedef struct s_map
{
	char		**grid;
	int			height;
	int			width;
}			t_map;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_textures	*textures;
	t_map		*map;
	t_player	*player;
	t_lalloc	*allocator;
}				t_data;

int		init_data(t_data **data, t_lalloc *allocator);
int		parse_file(char *filename, t_data **data);

void	clean_data(t_data *data);

void	debug_print_map(t_map *map);
void	debug_print_textures(t_textures *textures);
void	debug_print_player(t_player *player);
void	debug_print_data(t_data *data);


#endif