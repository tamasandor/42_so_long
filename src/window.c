/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 23:35:31 by atamas            #+#    #+#             */
/*   Updated: 2024/04/08 13:42:24 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx-linux/mlx_int.h"
#include "../mlx-linux/mlx.h"

int	window(void)
{
	void *mlx;
	void *mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "HAh");
	mlx_destroy_window(mlx, mlx_win);
	mlx_destroy_display(mlx);
	free(mlx);
	return (0);
}