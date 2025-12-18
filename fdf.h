/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   fdf.h                                               :+:    :+:           */
/*                                                      +:+                   */
/*   By: jualissa <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/12/17 17:25:39 by jualissa       #+#    #+#                */
/*   Updated: 2025/12/17 17:25:40 by jualissa       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "minilibx-linux/mlx.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "get_next_line/get_next_line.h"
# include <fcntl.h>
# include "libft/libft.h"
# include <math.h>

typedef struct s_fdf
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*ptr_first_pixel;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		win_length;
	int		win_height;

	float	dx;
	float	dy;
	float	steps;
	float	x_inc;
	float	y_inc;
	float	x;
	float	y;
	int		i;
	int		fd;
	int		**z_axe;
	int		map_len;
	int		map_height;
	char	**tmp;

	int		map_x;
	int		map_y;
	int		x0;
	int		y0;
	int		x1;
	int		y1;
	int		argc;
	char	**argv;
	int		zoom;

	int		tmp_x0;
	int		tmp_x1;
	int		tmp_y0;
	int		tmp_y1;
}	t_fdf;

void	parse_map(t_fdf *fdf);
void	fill_z_axe(t_fdf *fdf);
void	malloc_z_axe(t_fdf *fdf);
void	size_map(t_fdf *fdf);
int		count_words(char **str);
void	free_table(char **str);

void	put_line(t_fdf *value);
void	put_pixel(t_fdf *value, int x, int y);

void	wrong_arg(int argc);
int		key_hook(int keycode, t_fdf *fdf);
void	free_int_table(int **table, int map_height);
int		close_window(t_fdf *fdf);
void	draw_map(t_fdf *fdf);
int		mouse_zoom(int button, int x, int y, t_fdf *fdf);
void	free_table(char **str);

#endif
