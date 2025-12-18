/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   parcing_map.c                                       :+:    :+:           */
/*                                                      +:+                   */
/*   By: jualissa <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/12/17 17:26:08 by jualissa       #+#    #+#                */
/*   Updated: 2025/12/17 17:26:09 by jualissa       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	count_words(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

void	size_map(t_fdf *fdf)
{
	char	*line;

	fdf->map_height = 0;
	fdf->map_len = 0;
	line = get_next_line(fdf->fd);
	while (line)
	{
		fdf->tmp = ft_split(line, ' ');
		if (fdf->map_len == 0)
			fdf->map_len = count_words(fdf->tmp);
		free_table(fdf->tmp);
		free(line);
		fdf->map_height++;
		line = get_next_line(fdf->fd);
	}
}

void	malloc_z_axe(t_fdf *fdf)
{
	int	i;

	i = 0;
	fdf->z_axe = malloc(sizeof(int *) * fdf->map_height);
	if (!fdf->z_axe)
		return ;
	while (i < fdf->map_height)
	{
		fdf->z_axe[i] = malloc(sizeof(int) * fdf->map_len);
		if (!fdf->z_axe[i])
			return ;
		i++;
	}
}

void	fill_z_axe(t_fdf *fdf)
{
	int		y;
	int		x;
	char	*line;

	y = 0;
	line = get_next_line(fdf->fd);
	while (line)
	{
		fdf->tmp = ft_split(line, ' ');
		x = 0;
		while (x < fdf->map_len)
		{
			fdf->z_axe[y][x] = ft_atoi(fdf->tmp[x]);
			x++;
		}
		free_table(fdf->tmp);
		free(line);
		y++;
		line = get_next_line(fdf->fd);
	}
}

void	parse_map(t_fdf *fdf)
{
	size_map(fdf);
	close(fdf->fd);
	fdf->fd = open(fdf->argv[1], O_RDONLY);
	if (fdf->fd < 0)
	{
		write(2, "cant acces to this file\n", 24);
		exit(1);
	}
	malloc_z_axe(fdf);
	fill_z_axe(fdf);
	close(fdf->fd);
}
