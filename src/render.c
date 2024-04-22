/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:23:48 by atamas            #+#    #+#             */
/*   Updated: 2024/04/22 23:45:12 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void render(t_vars *vars)
{
    int x, y;
    int viewport_size = 7;  // Number of tiles from the player to display in each direction
    int tile_size = 64;     // Size of each tile in pixels

    // Calculate viewport boundaries
    int start_x = vars->mapchars->player_x - viewport_size;
    int start_y = vars->mapchars->player_y - viewport_size;
    int end_x = vars->mapchars->player_x + 25;
    int end_y = vars->mapchars->player_y + 11;

    // Clamp the viewport to the map boundaries
    start_x = (start_x < 0) ? 0 : start_x;
    start_y = (start_y < 0) ? 0 : start_y;
    end_x = (end_x >= vars->len_x) ? vars->len_x - 1: end_x;
    end_y = (end_y >= vars->len_y) ? vars->len_y - 1 : end_y;
	start_x = ((vars->mapchars->player_x > (end_x - start_x) / 2) && end_x - 29 > -1) ? (end_x - 29) : start_x;
	start_y = (vars->mapchars->player_y > ((end_y - start_y) / 2) && end_y - 18 > -1) ? (end_y - 18) : start_y;
    // Render only the tiles within the viewport
    for (y = start_y; y <= end_y; y++)
    {
        for (x = start_x; x <= end_x; x++)
        {
            char tile = vars->map[y][x];
            void *img = NULL;
            if (tile == '0')
                img = vars->empty;
            else if (tile == '1')
                img = vars->wall;
            else if (tile == 'C')
                img = vars->money;
            else if (tile == 'P')
                img = vars->player;

            if (img != NULL)
                mlx_put_image_to_window(vars->mlx, vars->win, img, (x - start_x) * tile_size, (y - start_y) * tile_size);
        }
    }
	// mlx_put_image_to_window(vars->mlx, vars->win, backg, 0, 0);
}
