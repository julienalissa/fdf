/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   fdf.c                                               :+:    :+:           */
/*                                                      +:+                   */
/*   By: jualissa <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/12/17 17:25:32 by jualissa       #+#    #+#                */
/*   Updated: 2025/12/17 17:25:35 by jualissa       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_value(t_fdf *fdf, int argc, char **argv)
{
	fdf->argc = argc;
	fdf->argv = argv;
	fdf->zoom = 25;
	fdf->fd = open(fdf->argv[1], O_RDONLY);
	if (fdf->fd < 0)
	{
		write(2, "cant acces to this file\n", 24);
		exit(1);
	}
	fdf->win_length = 1920;
	fdf->win_height = 1080;
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, fdf->win_length,
			fdf->win_height, "FdF");
	fdf->img = mlx_new_image(fdf->mlx, fdf->win_length,
			fdf->win_height);
	fdf->ptr_first_pixel = mlx_get_data_addr(fdf->img, &fdf->bits_per_pixel,
			&fdf->line_length, &fdf->endian);
}

void	iso_projection(int *x, int *y, int z)
{
	int	tmp_x;
	int	tmp_y;

	tmp_x = *x;
	tmp_y = *y;
	*x = (tmp_x - tmp_y) * cos(0.60);
	*y = (tmp_x + tmp_y) * sin(0.60) - z;
}

void	line_down_right(t_fdf *fdf)
{
	int	z;

	if (fdf->map_x < fdf->map_len - 1)
	{
		fdf->x1 = (fdf->map_x + 1) * fdf->zoom;
		fdf->y1 = fdf->map_y * fdf->zoom;
		z = fdf->z_axe[fdf->map_y][fdf->map_x + 1];
		iso_projection(&fdf->x1, &fdf->y1, z);
		put_line(fdf);
	}
	if (fdf->map_y < fdf->map_height - 1)
	{
		fdf->x1 = fdf->map_x * fdf->zoom;
		fdf->y1 = (fdf->map_y + 1) * fdf->zoom;
		z = fdf->z_axe[fdf->map_y + 1][fdf->map_x];
		iso_projection(&fdf->x1, &fdf->y1, z);
		put_line(fdf);
	}
}

void	draw_map(t_fdf *fdf)
{
	int	z;

	if (fdf->img)
		mlx_destroy_image(fdf->mlx, fdf->img);
	fdf->img = mlx_new_image(fdf->mlx, fdf->win_length, fdf->win_height);
	fdf->ptr_first_pixel = mlx_get_data_addr(fdf->img, &fdf->bits_per_pixel,
			&fdf->line_length, &fdf->endian);
	fdf->map_x = 0;
	fdf->map_y = 0;
	while (fdf->map_y < fdf->map_height)
	{
		fdf->map_x = 0;
		while (fdf->map_x < fdf->map_len)
		{
			fdf->x0 = fdf->map_x * fdf->zoom;
			fdf->y0 = fdf->map_y * fdf->zoom;
			z = fdf->z_axe[fdf->map_y][fdf->map_x];
			iso_projection(&fdf->x0, &fdf->y0, z);
			line_down_right(fdf);
			fdf->map_x++;
		}
		fdf->map_y++;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	wrong_arg(argc);
	set_value(&fdf, argc, argv);
	parse_map(&fdf);
	draw_map(&fdf);
	mlx_hook(fdf.win, 17, 0, close_window, &fdf);
	mlx_key_hook(fdf.win, key_hook, &fdf);
	mlx_mouse_hook(fdf.win, mouse_zoom, &fdf);
	mlx_loop(fdf.mlx);
	return (0);
}
