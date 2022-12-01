/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shabibol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:59:50 by shabibol          #+#    #+#             */
/*   Updated: 2022/12/01 16:59:52 by shabibol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "cub3D.h"

// void	draw_minimap(t_cub *cub)
// {
// 	int	x;
// 	int	y;
// 	// int	tile_l;
// 	// int	tile_w;

// 	// tile_l = (WINDOW_LENGTH / 4) / cub->maph;
// 	// tile_w = (WINDOW_WIDTH / 8) /cub->mapw;
// 	x = 0;
// 	while (x < WINDOW_LENGTH / 4)//270
// 	{
// 		y = 0;
// 		while (y < WINDOW_WIDTH / 8)//240
// 		{
// 			printf("x is %d, y is %d\n", x, y);
// 			if (cub->map[x % cub->maph][y % cub->mapw] == '1')
// 				img_pix_put(cub, cub->img, x, y, 256);//black
// 			else
// 				img_pix_put(cub, cub->img, x, y, 16777215);//white
// 			y++;
// 		}
// 		x++;
// 	}
// }
