/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillar <aguillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:20:51 by aguillar          #+#    #+#             */
/*   Updated: 2022/11/29 15:30:29 by aguillar         ###   ########.fr       */
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
	else if (keycode == cub->xk_n)
	{
		if (cub->map[(int)(cub->posy - 0.100001)][(int)(cub->posx)] == '0')
			cub->hooky -= 0.1;
	}
	else if (keycode == cub->xk_s)
	{
		if (cub->map[(int)(cub->posy + 0.100001)][(int)(cub->posx)] == '0')
			cub->hooky += 0.1;
	}
	else if (keycode == cub->xk_e)
	{
		if (cub->map[(int)(cub->posy)][(int)(cub->posx + 0.100001)] == '0')
			cub->hookx += 0.1;
	}
	else if (keycode == cub->xk_w)
	{
		if (cub->map[(int)(cub->posy)][(int)(cub->posx - 0.100001)] == '0')
			cub->hookx -= 0.1;
	}
	else if (keycode == XK_Right)
	{
		cub->hookangle -= 1;
		if (cub->hookangle == -1)
			cub->hookangle = 359;
		update_keycodes(cub);
	}
	else if (keycode == XK_Left)
	{
		cub->hookangle += 1;
		if (cub->hookangle == 360)
			cub->hookangle = 0;
		update_keycodes(cub);
	}
	cub3D_render_pos(cub, cub->hit_str);
	return (1);
}

void	update_keycodes(t_cub *cub)
{
	int	 dir;

	dir = cub->hookangle + 33;
	if (dir > 359)
		dir -= 360;
	if (dir > 45 && dir <= 135)
	{
		cub->xk_n = XK_w;
		cub->xk_s = XK_s;
		cub->xk_w = XK_a;
		cub->xk_e = XK_d;
	}
	else if (dir > 135 && dir <= 225)
	{
		cub->xk_n = XK_d;
		cub->xk_s = XK_a;
		cub->xk_w = XK_w;
		cub->xk_e = XK_s;
	}
	else if (dir > 225 && dir <= 315)
	{
		cub->xk_n = XK_s;
		cub->xk_s = XK_w;
		cub->xk_w = XK_d;
		cub->xk_e = XK_a;
	}
	else
	{
		cub->xk_n = XK_a;
		cub->xk_s = XK_d;
		cub->xk_w = XK_s;
		cub->xk_e = XK_w;
	}
}
