/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillar <aguillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:20:51 by aguillar          #+#    #+#             */
/*   Updated: 2022/11/08 14:53:03 by aguillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	handle_no_event(void *data)
{
	(void)data;
	return (0);
}

int	key_hook(int keycode, t_cub *cub)
{
	if (keycode == XK_Escape)
		ft_exit(cub);
	else if (keycode == XK_w)
	{
		if (cub->map[(int)(cub->posY) - 1][(int)(cub->posX)] == '0')
			cub->posY -= 0.1;
	}
	else if (keycode == XK_s)
	{
		if (cub->map[(int)(cub->posY) + 1][(int)(cub->posX)] == '0')
			cub->posY += 0.1;
	}
	else if (keycode == XK_d)
	{
		if (cub->map[(int)(cub->posY)][(int)(cub->posX) + 1] == '0')
			cub->posX += 0.1;
	}
	else if (keycode == XK_a)
	{
		if (cub->map[(int)(cub->posY)][(int)(cub->posX) - 1] == '0')
			cub->posX -= 0.1;
	}
	else if (keycode == XK_Right)
	{
		cub->base_angle -= 1;
		if (cub->base_angle == -1)
			cub->base_angle = 359;
	}
	else if (keycode == XK_Left)
	{
		cub->base_angle += 1;
		cub->base_angle %= 360;
	}
	return (1);
}
