/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   put_line.c                                          :+:    :+:           */
/*                                                      +:+                   */
/*   By: jualissa <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/12/17 17:26:15 by jualissa       #+#    #+#                */
/*   Updated: 2025/12/17 17:26:16 by jualissa       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_pixel(t_fdf *fdf, int x, int y)
{
	char	*dst;
	int		color;
	int		tmp;

	color = 0x000000FF;
	if (x < 0 || y < 0 || x >= fdf->win_length || y >= fdf->win_height)
		return ;
	tmp = x * (fdf->bits_per_pixel / 8);
	dst = fdf->ptr_first_pixel + (y * fdf->line_length + tmp);
	*(unsigned int *)dst = color;
}

void	reverse_neg_signe(float *num)
{
	if (*num < 0)
		*num = *num * -1;
}

void	define_steps(t_fdf *fdf, int x0, int x1)
{
	if (fdf->dx > fdf->dy)
		fdf->steps = fdf->dx;
	else
		fdf->steps = fdf->dy;
	if (x1 >= x0)
		fdf->x_inc = (x1 - x0) / fdf->steps;
	else
		fdf->x_inc = (x0 - x1) / (-fdf->steps);
}

void	define_y_inc(t_fdf *fdf, int y0, int y1)

{
	if (y1 >= y0)
		fdf->y_inc = (y1 - y0) / fdf->steps;
	else
		fdf->y_inc = (y0 - y1) / (-fdf->steps);
}

void	put_line(t_fdf *fdf)
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;

	x0 = fdf->x0 + 500;
	y0 = fdf->y0 + 300;
	x1 = fdf->x1 + 500;
	y1 = fdf->y1 + 300;
	fdf->dx = x1 - x0;
	reverse_neg_signe(&fdf->dx);
	fdf->dy = y1 - y0;
	reverse_neg_signe(&fdf->dy);
	define_steps(fdf, x0, x1);
	define_y_inc(fdf, y0, y1);
	fdf->x = x0;
	fdf->y = y0;
	fdf->i = 0;
	while (fdf->i <= (int)fdf->steps)
	{
		put_pixel(fdf, (int)(fdf->x + 0.5f), (int)(fdf->y + 0.5f));
		fdf->x += fdf->x_inc;
		fdf->y += fdf->y_inc;
		fdf->i++;
	}
}
