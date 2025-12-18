/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   hooks.c                                             :+:    :+:           */
/*                                                      +:+                   */
/*   By: jualissa <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/12/17 17:25:46 by jualissa       #+#    #+#                */
/*   Updated: 2025/12/17 17:26:01 by jualissa       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_int_table(int **table, int map_height)
{
	int	i;

	i = 0;
	if (!table)
		return ;
	while (i < map_height)
	{
		free(table[i]);
		i++;
	}
	free(table);
}

int	close_window(t_fdf *fdf)
{
	free_int_table(fdf->z_axe, fdf->map_height);
	if (fdf->img)
		mlx_destroy_image(fdf->mlx, fdf->img);
	if (fdf->win)
		mlx_destroy_window(fdf->mlx, fdf->win);
	if (fdf->mlx)
	{
		mlx_destroy_display(fdf->mlx);
		free(fdf->mlx);
	}
	exit(0);
}

int	key_hook(int keycode, t_fdf *fdf)
{
	if (keycode == 65307)
		close_window(fdf);
	return (0);
}

void	wrong_arg(int argc)
{
	if (argc != 2)
	{
		write(2, "need ./fdf map\n", 15);
		exit(1);
	}
}

int	mouse_zoom(int button, int x, int y, t_fdf *fdf)
{
	(void)x;
	(void)y;
	if (button == 4)
		fdf->zoom = fdf->zoom + 1;
	else if (button == 5)
		fdf->zoom = fdf->zoom - 1;
	if (fdf->zoom < 1)
		fdf->zoom = 1;
	draw_map(fdf);
	return (0);
}
