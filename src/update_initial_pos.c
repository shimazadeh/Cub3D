/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_initial_pos.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillar <aguillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:16:16 by aguillar          #+#    #+#             */
/*   Updated: 2022/11/29 15:24:42 by aguillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	update_initial_pos(int i, int j, char dir, t_cub *cub)
{
	cub->posy = i + 0.5;
	cub->posx = j + 0.5;
	cub->hookx = cub->posx;
	cub->hooky = cub->posy;
	if (dir == 'N')
		cub->base_angle = 90 - 33;
	else if (dir == 'S')
		cub->base_angle = 270 - 33;
	else if (dir == 'E')
		cub->base_angle = 360 - 33;
	else if (dir == 'W')
		cub->base_angle = 180 - 33;
	cub->hookangle = cub->base_angle;
	update_keycodes(cub);
}
