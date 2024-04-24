/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:23:48 by atamas            #+#    #+#             */
/*   Updated: 2024/04/24 14:06:09 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	assign_calculations(t_vars *vars, int *sx, int*sy, int *ex, int *ey)
{
	*sx = vars->mapchars->player_x - 7;
	*sy = vars->mapchars->player_y - 14;
	*ex = vars->mapchars->player_x + 29;
	*ey = vars->mapchars->player_y + 14;
	if (*sx < 0)
		*sx = 0;
	if (*sy < 0)
		*sy = 0;
	if (*ex >= vars->len_x)
		*ex = vars->len_x - 1;
	if (*ey >= vars->len_y)
		*ey = vars->len_y - 1;
	if ((vars->mapchars->player_x > (*ex - *sx) / 2) && *ex - 29 > -1)
		*sx = *ex - 29;
	if (vars->mapchars->player_y > 14 && *ey - 16 > -1)
		*sy = *ey - 16;
}

void	render_x(t_vars *vars, int x, int y, void *img, int end_x, int start_x, int start_y)
{
	char	tile;
	int		x_pos;
	int		y_pos;

	while (x <= end_x)
	{
		tile = vars->map[y][x];
		img = NULL;
		if (tile == '0')
			img = vars->empty;
		else if (tile == '1')
			img = vars->wall;
		else if (tile == 'C')
			img = vars->money;
		else if (tile == 'P')
			img = vars->player;
		x_pos = (x - start_x) * 64;
		y_pos = (y - start_y) * 64;
		if (img != NULL)
			mlx_put_image_to_window(vars->mlx, vars->win, img, x_pos, y_pos);
		x++;
	}
}

void	render(t_vars *vars)
{
	int		x;
	int		y;
	int		start_x;
	int		start_y;
	int		end_x;
	int		end_y;
	char	tile;

	assign_calculations(vars, &start_x, &start_y, &end_x, &end_y);
	y = start_y;
	while (y <= end_y)
	{
		x = start_x;
		render_x(vars, start_x, y, NULL, end_x, start_x, start_y);
		y++;
	}
}
