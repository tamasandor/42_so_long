/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:22:29 by atamas            #+#    #+#             */
/*   Updated: 2024/04/26 15:16:15 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	can_move(t_vars *vars, int new_x, int new_y)
{
	if (vars->map[new_y][new_x] == 'C')
	{
		vars->mapchars->collectible -= 1;
		vars->map[new_y][new_x] = 'P';
		return (1);
	}
	else if (vars->map[new_y][new_x] == 'E')
	{
		if (vars->mapchars->collectible == 0)
		{
			/* Put a screen instead */
			mlx_put_image_to_window(vars->mlx, vars->win, vars->wins, 0, 0);
			ft_printf("You won\n");
		}
		vars->map[new_y][new_x] = 'P';
		return (1);
	}
	else if (vars->map[new_y][new_x] == '0')
	{
		vars->map[new_y][new_x] = 'P';
		return (1);
	}
	return (0);
}

void	move_forward(t_vars *vars)
{
	int	new_y;
	int	x;

	new_y = vars->mapchars->player_y - 1;
	x = vars->mapchars->player_x;
	if (new_y >= 0 && can_move(vars, x, new_y))
	{
		vars->map[new_y + 1][x] = '0';
		vars->mapchars->player_y = new_y;
		vars->mapchars->movements += 1;
		ft_printf("Moves: %d\n", vars->mapchars->movements);
	}
}

void	move_backward(t_vars *vars)
{
	int	new_y;
	int	x;

	new_y = vars->mapchars->player_y + 1;
	x = vars->mapchars->player_x;
	if (new_y >= 0 && can_move(vars, x, new_y))
	{
		vars->map[new_y - 1][x] = '0';
		vars->mapchars->player_y = new_y;
		vars->mapchars->movements += 1;
		ft_printf("Moves: %d\n", vars->mapchars->movements);
	}
}

void	move_left(t_vars *vars)
{
	int	y;
	int	new_x;

	y = vars->mapchars->player_y;
	new_x = vars->mapchars->player_x - 1;
	if (new_x >= 0 && can_move(vars, new_x, y))
	{
		vars->map[y][new_x + 1] = '0';
		vars->mapchars->player_x = new_x;
		vars->mapchars->movements += 1;
		ft_printf("Moves: %d\n", vars->mapchars->movements);
	}
}

void	move_right(t_vars *vars)
{
	int	y;
	int	new_x;

	y = vars->mapchars->player_y;
	new_x = vars->mapchars->player_x + 1;
	if (new_x >= 0 && can_move(vars, new_x, y))
	{
		vars->map[y][new_x - 1] = '0';
		vars->mapchars->player_x = new_x;
		vars->mapchars->movements += 1;
		ft_printf("Moves: %p\n", vars->mapchars->movements);
	}
}
